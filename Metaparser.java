package psl.metaparser;

import java.util.*;
import java.io.*;
import java.net.*;

import siena.SienaException;

/** Root Metaparser class.
 *  Creates a SienaListenerThread, and establishes a few
 *  thread intercommunication data structures.
 *  If SienaListener gets a query from the Event Distiller,
 *  it starts a new SEParserThread.  The SEParserThread
 *  directs the data input of a subordinate Validator.
 *  This initial Validator validates against the smartevent
 *  schema.  When it encounters an unknown tag, the schema and
 *  processor for the unknown tag are requested from the Oracle, 
 *  and the thread  goes to sleep.  When the response comes in, the 
 *  Validator wakes up and validates the unknown portion.  When 
 *  finished, it checks to see if the worklet has arrived and 
 *  installed the tag processor.  If not, it goes to sleep again, 
 *  and waits for the arrival.  When it comes, it applies the tag 
 *  processor based on type: XSLT templates are applied, and 
 *  XMLFilters are hooked up to an XMLReader.
 *
 *  Maybe.
 *
 *  TODO: properties instead of hardcoding
 *  TODO: caching of oracle responses.
 *  TODO: reacting to unknown tag, instead of faking it based on
 *  FleXML PI.  Requires actual streaming validation.
 *
 *  $Log$
 *  Revision 2.4  2001-02-05 06:35:16  png3
 *  Post California version
 *
 *  Revision 2.3  2001/01/29 04:04:48  png3
 *  Added package psl.metaparser statements.  Can you say "Oops?"
 *
 *  Revision 2.2  2001/01/28 17:52:17  png3
 *  New version of Metaparser: fully multithreaded.  PrintWriter logs.
 *
 *
 */

public class Metaparser {
  
  /** when Parsers need to wait for a response, they register
    * themselves here (key=requestid, value=the object they're
    * wait()ing on, and wait for a notify().
    * Synchronized HashMap;
    */
  static Map waitList = null;
  SienaListenerThread slt = null;
  private static final String fn = "Metaparser";
  // should allow this from command line also...
  private static final String prop = "metaparser.properties";
  static boolean debug = false;
  private static String seSchema = null;
  static PrintWriter log = null;   
  static PrintWriter dbg = null;   

  public static void main(String args[]) {
    System.out.println("Metaparser starting up");

    Properties p = new Properties();
    try {
      FileInputStream fis = new FileInputStream(prop);
      p.load(fis);
    } catch (IOException ioe) {
      System.out.println(fn + ": Warning: can't open properties file " +
      	prop + ". Using defaults.");
      System.out.println(ioe);
    }

    String sienaURL = p.getProperty("sienaURL", 
    	"senp://canal.psl.cs.columbia.edu:4321");
    debug = Boolean.valueOf(p.getProperty("debug","false")).booleanValue();
    String logFile = p.getProperty("logFile", "Metaparser.log");
    String dbgFile = null;
    if (debug) {
      dbgFile = p.getProperty("dbgFile", "Metaparser.dbg");
    }
    seSchema = p.getProperty("seSchema", "SmartEventSchema.xsd");

    try {
      log = new PrintWriter(new FileWriter(logFile), true);
      log.println("Log started " + MPUtil.timestamp());
      if (debug) {
	dbg = new PrintWriter(new FileWriter(dbgFile), true);
	dbg.println("Debug Log started " + MPUtil.timestamp());
      }
    } catch (IOException ioe) {
      System.err.println(fn + ": Can't open log/debug file:");
      System.err.println(ioe);
      // abort
      return;
    }

    Metaparser mp = new Metaparser();
    waitList = Collections.synchronizedMap(new HashMap());
    // TODO: SienaListeners don't have to be threads...
    mp.slt = new SienaListenerThread(sienaURL, log, dbg);
    Thread t = new Thread(mp.slt);
    if (debug) dbg.println(fn + ": starting slt");  // debug
    t.start();
  }

  synchronized public static String getSESchema() {
    return seSchema;
  }
}
