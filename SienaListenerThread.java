package psl.metaparser;

import java.io.PrintWriter;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import siena.*;

/** Listener for incoming Siena events.
  * Spawns ParserThreads.
  *
  * $Log$
  * Revision 2.7  2001-11-14 04:43:55  valetto
  * Deals with the new micro Oracle; handles remote schemas and tagproceesors via URLs.
  * Also, substantially cleaned up code.
  *
  * Revision 2.6  2001/06/02 19:35:33  png3
  * various pre-demo tweaks
  *
  * Revision 2.5  2001/03/14 08:17:13  png3
  * various changes towards working demo
  *
  * Revision 2.4  2001/02/05 06:35:16  png3
  * Post California version
  *
  * Revision 2.3  2001/01/30 10:16:55  png3
  * Almost working...
  *
  * Revision 2.2  2001/01/29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.1  2001/01/28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
class SienaListenerThread implements Runnable {

  private Siena s = null;
  private String sienaURL = null;
  private PrintWriter log = null;
  private PrintWriter dbg = null;
  boolean debug = false;

  String hostname = null;
  private final String source = "psl.metaparser.SienaListenerThread";



  private static final int RECV_PORT = 31337;
  //TODO: get from sequencer somewhere
  static final int SRC_ID = 1;

  static int instance_counter = 0;

  SienaListenerThread (String sienaURL, PrintWriter log, PrintWriter dbg) {
    this.sienaURL = sienaURL;
    this.log = log;
    this.dbg = dbg;
    debug = (dbg != null);
    System.err.println("SLT started debug = " + debug);

    try {
      hostname = InetAddress.getLocalHost().getHostName();
    } catch (UnknownHostException uhe) {
      log.println("slt_ctor: can't get local host name:" + uhe);
      return;
    }
    prDbg("SLT starting up");
  }

  // TODO: not thread safe, but we're going to un-Thread this anyway...
  void prLog(String m) {log.println(m);}
  void prDbg(String m) {if (debug) dbg.println(m);}

  synchronized static int get_inst_nr() {
    return instance_counter++;
  }

  public void run() {

    final String fn = "slt_run";

    final HierarchicalDispatcher hd = new HierarchicalDispatcher();
    try {
      // debug
      if (dbg != null) dbg.println(fn + " setting recv port to " +
      	RECV_PORT + ", and sienaURL to " + sienaURL);
      hd.setReceiver(new TCPPacketReceiver(RECV_PORT));
      hd.setMaster(sienaURL);
    } catch (InvalidSenderException ise) {
      log.println(fn + ": Invalid Sender:" + ise);
      return;
    } catch (IOException ioe) {
      log.println(fn + ": Unable to set hd receiver:" + ioe);
      return;
    }

    // we have our Siena
    synchronized (this) {
      s = hd;
    }

    System.out.println("Subscribed to siena " + sienaURL);

    Runtime.getRuntime().addShutdownHook(new Thread() {
      public void run() {
	System.err.println("SLT shutting down");
	hd.shutdown();
      } }); 

    // create filters
    // #1, stuff coming from ED
    Filter f1 = new Filter();
    // f1.addConstraint("Source", "EventDistiller");
    f1.addConstraint("Type", "DataToMetaparser");
    // debug
    if (dbg != null) dbg.println("adding DataToMetaparser filter " + f1);
    try {
      synchronized (this) {
	s.subscribe(f1, 
	  new Notifiable() {
	    public void notify(Notification n) {handleEDNotification(n);}
	    public void notify(Notification[] s) {}
	  }
	);
      }
    } catch (SienaException se) {
      log.println(fn + ": SienaException adding DataToMetaparserfilter:");
      log.println(se);
      return;
    }

    // #2: from Oracle
    Filter f2 = new Filter();
    f2.addConstraint("Source", "psl.oracle.OracleSienaInterface");
    f2.addConstraint("Type", "OracleQueryResult");
    // TODO: when Oracle sends it, subscribe to it...
    f2.addConstraint("MPHostname", hostname);
    f2.addConstraint("MPSourceID", SRC_ID);
    // debug
    if (dbg != null) dbg.println(fn + " adding Oracle filter " + f2);
    try {
      synchronized (this) {
	s.subscribe(f2, 
	  new Notifiable() {
	    public void notify(Notification n) {handleOracleNotification(n);}
	    public void notify(Notification[] s) {}
	  }
	);
      }
    } catch (SienaException se) {
      log.println(fn + ": SienaException adding filter 2:");
      log.println(se);
      return;
    }
  }

  public void handleEDNotification(Notification n) {
    final String fn="handleEDNotification: ";
    if (dbg != null) {  // debug
      dbg.println("hEN(): got ED notification:" + n);
    }
    AttributeValue se = n.getAttribute("SmartEvent");
    prLog(fn+"Received event from EventDistiller.  Starting ParserThread " +
    	MPUtil.timestamp());
    ParserThread pt = new ParserThread(se.stringValue(), 
    	get_inst_nr(), this, (dbg != null));
    Thread t = new Thread(pt);
    t.start();
  }

  public void handleOracleNotification(Notification n) {
    String reqID = null;
    final String fn="hON: ";

    prDbg(fn+"got Oracle notification" + n);
    

    // TODO: check for not found
    AttributeValue se = n.getAttribute("MPRequestID");
    reqID = se.stringValue();

    Object o = Metaparser.waitList.get(reqID);
    // replace hash entry with oracle xml
    prDbg(fn+"Hash replace: key="+reqID+"; val="+n.toString());
    Metaparser.waitList.put(reqID, n);
    prDbg(fn+"notifying...");
    synchronized(o) {
      // wakey, wakey
      o.notify();
    }
  }

  // synchronized wrapper
  synchronized public void publish(Notification n) {
    final String fn = "SLT_publish: ";
    prDbg("publishing " + n); 
    try {
      s.publish(n);
    } catch (SienaException se) {
      log.println(fn+"SienaException while publishing " + n);
      log.println(se);
      return;
    }
  }

}
