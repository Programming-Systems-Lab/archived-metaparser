package psl.metaparser;

import java.io.*;
import java.net.*;
import java.util.*;

import siena.*;

/** Generates ED-like XML notification.
  * One argument: xml message to include.
  *
  * $Log$
  * Revision 2.3  2001-01-30 10:16:55  png3
  * Almost working...
  *
  * Revision 2.2  2001/01/29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.1  2001/01/28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
public class SienaTest {

  /** Constructor */
  public static void main(String[] args) {

    String xml = null;
    String s;

    HierarchicalDispatcher hd = new HierarchicalDispatcher();
    try {
      hd.setReceiver(new TCPPacketReceiver(31339));
      hd.setMaster("senp://canal.psl.cs.columbia.edu:4321");
    } catch (IOException ioe) {
      System.err.println("Unable to set hd receiver:" + ioe);
      return;
    } catch (InvalidSenderException ise) {
      System.err.println("Invalid Sender:" + ise);
      return;
    }

    System.err.println("Reading test file " + args[0]);
    StringBuffer sb = new StringBuffer();
    s = null;
    try {
      BufferedReader tf_br = new BufferedReader(new FileReader(args[0]));
      do {
	s = tf_br.readLine();
	if (s != null) {
	  sb.append(s);
	  sb.append("\n");
	}
      } while (s != null);
    } catch (IOException ioe) {
      System.err.println("Exception when reading " + args[0] + ":" + ioe);
      return;
    }
    xml = sb.toString();
    System.err.println("About to parse:\n" + xml+"\n.");

    Notification n = new Notification();
    n.putAttribute("Source", "EventDistiller");
    n.putAttribute("Type", "DataToMetaParser");
    n.putAttribute("SmartEvent", xml);

    try {
      hd.publish(n);
    } catch (SienaException se) {
      System.err.println("Siena exception on publish:" + se);
      return;
    }
    hd.shutdown();
  }
}