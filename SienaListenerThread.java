import java.io.PrintWriter;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import siena.HierarchicalDispatcher;
import siena.Siena;
import siena.SienaException;
import siena.Notification;
import siena.Notifiable;
import siena.Filter;
import siena.AttributeValue;
import siena.TCPPacketReceiver;
import siena.InvalidSenderException;

/** Listener for incoming Siena events.
  * Spawns ParserThreads.
  *
  * $Log$
  * Revision 2.1  2001-01-28 17:52:17  png3
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
    debug = (dbg == null);

    try {
      hostname = InetAddress.getLocalHost().getHostName();
    } catch (UnknownHostException uhe) {
      log.println("slt_ctor: can't get local host name:" + uhe);
      return;
    }
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

    Runtime.getRuntime().addShutdownHook(new Thread() {
      public void run() {
	System.err.println("SLT shutting down");
	hd.shutdown();
      } }); 
    // create filters
    // #1, stuff coming from ED
    Filter f1 = new Filter();
    f1.addConstraint("Source", "EventDistiller");
    f1.addConstraint("Type", "DataToMetaParser");
    // debug
    if (dbg != null) dbg.println("adding ED filter " + f1);
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
      log.println(fn + ": SienaException adding filter 1:");
      log.println(se);
      return;
    }

    // #2: from Oracle
    Filter f2 = new Filter();
    f2.addConstraint("source", "psl.oracle.impl.OracleSienaInterface");
    f2.addConstraint("type", "queryResult");
    // TODO: when Oracle sends it, subscribe to it...
    f2.addConstraint("MPHostname", hostname);
    f2.addConstraint("MPSrcID", SRC_ID);
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
    if (dbg != null) {  // debug
      dbg.println("hEN(): got ED notification:" + n);
    }
    AttributeValue se = n.getAttribute("SmartEvent");
    ParserThread pt = new ParserThread(se.stringValue(), 
    	get_inst_nr(), this, (dbg != null));
    Thread t = new Thread(pt);
    t.start();
  }

  public void handleOracleNotification(Notification n) {
    String reqID = null;
    String oracleResp = null;
    final String fn="hON: ";

    prDbg(fn+"got Oracle notification" + n);
    

    // TODO: check for not found
    AttributeValue se = n.getAttribute("MPRequestID");
    reqID = se.stringValue();
    se = n.getAttribute("value");
    oracleResp = se.stringValue();

    Object o = Metaparser.waitList.get(reqID);
    // replace hash entry with oracle xml
    prDbg(fn+"Hash replace: key="+reqID+"; val="+oracleResp);
    Metaparser.waitList.put(reqID, oracleResp);
    prDbg(fn+"notifying...");
    synchronized(o) {
      // wakey, wakey
      o.notify();
    }
  }

  // synchronized wrapper
  synchronized public void publish(Notification n) {
    final String fn = "SLT_publish: ";
    if (dbg != null) { dbg.println("publishing " + n); } // debug
    try {
      s.publish(n);
    } catch (SienaException se) {
      log.println(fn+"SienaException while publishing " + n);
      log.println(se);
      return;
    }
  }

}
