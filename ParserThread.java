package psl.metaparser;

import org.xml.sax.*;
import org.xml.sax.helpers.*;
import org.apache.xerces.parsers.*;

// import psl.worklets.*;
import psl.codetransfer.*;
import psl.kx.*;

import siena.*;

import java.io.*;
import java.net.*;
import java.util.*;

import psl.tagprocessor.TagProcessor;

/** Handles the parsing one input XML message.
  * Spawns Validators/SubParsers to validate subcomponents.
  *
  * $Log$
  * Revision 2.14  2004-03-25 19:41:06  janak
  * Removed unused worklets dependency
  *
  * Revision 2.13  2001/11/14 04:43:55  valetto
  * Deals with the new micro Oracle; handles remote schemas and tagproceesors via URLs.
  * Also, substantially cleaned up code.
  *
  * Revision 2.12  2001/06/02 19:35:33  png3
  * various pre-demo tweaks
  *
  * Revision 2.11  2001/04/18 20:12:29  png3
  * synchronization III: insertion of null object unnecessary and removed
  *
  * Revision 2.10  2001/04/18 19:55:18  png3
  * fixed idiot error (program is unlikely to loop if there's no while statement...)
  *
  * Revision 2.9  2001/04/18 19:49:50  png3
  * modified synchronization method for worklet arrival.  I thought incorrectly
  * that wait()-ing on an object released _all_ of its locks
  *
  * Revision 2.8  2001/04/11 18:55:17  png3
  * fixed bug with not storing object ref in _wklArrivals
  *
  * Revision 2.7  2001/03/14 08:17:13  png3
  * various changes towards working demo
  *
  * Revision 2.6  2001/03/12 08:07:39  png3
  * now links with worklets.*
  *
  * Revision 2.5  2001/02/05 06:35:16  png3
  * Post California version
  *
  * Revision 2.4  2001/01/30 10:16:55  png3
  * Almost working...
  *
  * Revision 2.3  2001/01/29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.2  2001/01/29 03:55:34  png3
  * zapping Def.java.  Replaced by the superior Simin tagprocessor stuff
  *
  * Revision 2.1  2001/01/28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
class ParserThread extends DefaultHandler 
	implements Runnable, ClassFileReceiver {

  String xml = null;
  int instNr = 0;
  Locator loc = null;
  SienaListenerThread slt = null;
  PrintWriter log = null;
  PrintWriter dbg = null;
  boolean debug = false;
  int depth = 0;

  String moduleName = null;

  Stack valStack = null;
  Validator currentVal = null;
  boolean spawnParser = false;
  String currentHint = null;

  private final String source = "psl.metaparser.ParserThread";
  String requestID = null;

  public ParserThread(String xml, int instNr, 
  	SienaListenerThread slt, boolean debug) {
    this.xml = xml;
    this.instNr = instNr;
    this.slt = slt;
    this.debug = debug;
  }

  public String targetLocation() {return ".";}

  public void classesDelivered() {
    System.err.println("Classes have been delivered!");
  }

  void prLog(String m) {log.println(m);}
  void prDbg(String m) {if (debug) dbg.println(m);}

  public void run() {
    final String fn = "PT_run(): ";
  
    try {
      log = new PrintWriter(new FileWriter("PT"+instNr+".log"), true);
      log.println("Log started " + MPUtil.timestamp());
      if (debug) {
	dbg = new PrintWriter(new FileWriter("PT"+instNr+".dbg"), true);
	dbg.println("Debug Log started " + MPUtil.timestamp());
      }
    } catch (IOException ioe) {
      System.err.println(fn + "unable to open log files");
      System.err.println(ioe);
      return;
    }

    valStack = new Stack();
   
    Hashtable ht = new Hashtable();
    SAXParser p = new SAXParser();
    p.setContentHandler(this);
    p.setErrorHandler(this);
    try {
      p.setFeature("http://xml.org/sax/features/validation", false);
      p.setFeature("http://xml.org/sax/features/namespaces", true);
      p.setFeature("http://apache.org/xml/features/validation/schema", false);
    } catch (SAXNotRecognizedException snre) {
      prLog(fn+"Exception setting feature:" + snre.getMessage());
      return;
    } catch (SAXNotSupportedException snse) {
      prLog(fn+"Feature not supported:" + snse.getMessage());
      return;
    }
 
    if (debug) dbg.println(fn+"creating new validator");  // debug
    try {
      currentVal = new Validator(xml, new PipedWriter(),
      	"SEValid" + instNr, debug);
      // initialize outermost depth
      currentVal.setDepth(-1);
      currentVal.setElement(null);

      if (debug) dbg.println(fn+"starting to parse");  // debug
      p.parse(new InputSource(new StringReader(xml)));
      currentVal.close(true);

      prDbg(fn+"checking for processor");  // debug
      if (moduleName != null) {

	prDbg(fn+"module "+moduleName+" should be coming");  // debug

	try {
	// Let Simin work his magic
	  URL[] jarPath = new URL[]{new URL(moduleName)};
	  URLClassLoader loader = new URLClassLoader(jarPath); // this can remote tagprocessor modules
	  Class cls = Class.forName
	      ("psl.tagprocessor.TagProcessorImpl", true, loader);
	      
	  XMLReader reader = XMLReaderFactory.createXMLReader
	  ("org.apache.xerces.parsers.SAXParser");
	  try {
	    reader.setFeature("http://xml.org/sax/features/validation", false);
	    reader.setFeature("http://xml.org/sax/features/namespaces", true);
	    reader.setFeature("http://apache.org/xml/features/validation/schema", false);
	  } catch (SAXNotRecognizedException snre) {
	    prLog(fn+"Exception setting feature:" + snre.getMessage());
	    return;
	  } catch (SAXNotSupportedException snse) {
	    prLog(fn+"Feature not supported:" + snse.getMessage());
	    return;
	  }
	  TagProcessor tp = (TagProcessor) cls.newInstance();

	  /* PEPPO: this requires that a .jar is downloaded locally 
	     and accessed via filename
	  */
	  //tp.setResource(moduleName);
	  
	  /* PEPPO new - attempts to use remote .jar via its URL */
	  tp.setResource(new URL(moduleName));
	  tp.init(ht);
	  reader.setContentHandler(tp.getContentHandler());
	  dbg.println(fn+"TagProcessor about to parse");
	  reader.parse(new InputSource(new StringReader(xml)));
	  dbg.println(fn+"TagProcessor about to process");
	  tp.process();
	} catch (Exception e) {
	  log.println("Error during TagProcessor Execution:" + e);
	  e.printStackTrace();
	  return;
	}

	prDbg(fn+"Resulting Hashtable is: " + ht);
	// TODO what's my number?
	// Demo Temp
	AttributeValue av = (AttributeValue)ht.get("Status");
	if ((av == null) || !(av.stringValue().equals("Running"))) {
	  KXNotification edAlert = KXNotification.EDInputKXNotification(
					  "psl.metaparser.ParserThread", 0, ht);
	  slt.publish(edAlert);
	}
	
     }

    } catch (Exception e) {
      log.println(fn+"Exception during parsing at " + 
      	MPUtil.printLoc(loc));
      log.println(e);
      e.printStackTrace();
      return;
    }
    if (debug) dbg.println(fn+"Done parsing");
  }

  public void setDocumentLocator(Locator loc) {

    final String fn = "PT_setDocLoc: ";

    prDbg(fn+"SetDocumentLocator:");
    this.loc = loc;
  }

  public void startDocument() {

    final String fn = "PT_startDoc: ";

    prDbg(fn+"StartDocument");
  }

  public void endDocument() throws SAXException {

    final String fn = "PT_endDoc: ";

    prDbg(fn+"EndDocument");
  }

  public void startElement(
          String namespaceURI, String localName, String qName, Attributes atts)
            throws SAXException {

    final String fn = "PT_startElement: ";
    Notification oracleResp = null;

    prDbg(fn+MPUtil.printLoc(loc) + ":" + qName);
    for (int i = 0; i < atts.getLength(); i++) {
      String aname = atts.getQName(i);
      String type  = atts.getType(i);
      String value = atts.getValue(i);

      prDbg(fn+"   " + aname + "(" + type + ")" + "=" + value);
    }
    if (spawnParser) {
      prDbg(fn+"*** pushing currentVal");
      valStack.push(currentVal);

      // retrieve subparser
      requestID = String.valueOf(System.currentTimeMillis());

      Notification n = new Notification();
      n.putAttribute("Hostname", slt.hostname);
      n.putAttribute("Source", source);
      n.putAttribute("SourceID", slt.SRC_ID);
      n.putAttribute("RequestID", requestID);
      // changed to MPQuery for Oracle compatibility
      n.putAttribute("Type", "MPQuery");
      n.putAttribute("MPQuery", MPUtil.makeQuery(qName));
      // PEPPO: added to send pre-selected hint to Oracle about what tag processor to use
      if (currentHint != null)
      	n.putAttribute("useHint", currentHint);
      prDbg(fn+"sending request to Oracle:" + n);
      try {      
	slt.publish(n);
	Object lockObj = new Object();
	Metaparser.waitList.put(requestID, lockObj);
	prDbg(fn+"going to sleep: " + MPUtil.timestamp());
	synchronized (lockObj) {
	  lockObj.wait();
	}
	prDbg(fn+"awake again: " + MPUtil.timestamp());
	// hash entry now has the Event returned by the Oracle
	oracleResp = (Notification)Metaparser.waitList.get(requestID);
	prDbg(fn+"retrieved OResp of:"+oracleResp.toString());
	String schemaURL = MPUtil.extractSchemaURLFromEvent(oracleResp);
	moduleName = MPUtil.extractModuleNameFromEvent(oracleResp);
      
	// we have a new schema.  parse it out, suck it in...
	currentVal = new Validator(xml, new PipedWriter(),
	  "SubValid" + instNr, debug, loc);
	currentVal.send("<?xml version='1.0' encoding='UTF-8'?>");
	/* PEPPO: uses the URL of the schema to specify to the validator
	   the schema into the fabricated xml header	
	*/
	currentVal.send("<"+qName+
		" xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'" +
  		" xsi:noNamespaceSchemaLocation='" + schemaURL +"'>");
      } catch (Exception e) {
	prLog(fn+"Exception with Oracle communication: " + e);
	e.printStackTrace();
      }

      prDbg(fn+"*** Saving depth info of depth:" + depth
        + ", targetElement:" + qName);
      currentVal.setDepth(depth);
      currentVal.setElement(qName);
      spawnParser = false;
      currentHint = null;
    }

    // finally, spit out this tag
    try {
      currentVal.flush(loc);
    } catch (IOException ioe) {
      prLog(fn+"Flush error:" + ioe);
    }
    ++depth;
  }


  public void endElement(String namespaceURI, String localName, String qName) 
  	throws SAXException {
    final String fn = "PT endElement: ";
    --depth;
    prDbg(fn + qName);
    try {
      currentVal.flush(loc);
    } catch (IOException ioe) {
      prDbg(fn+"Flush error:" + ioe);
    }
    if ((currentVal.getDepth() == depth) && 
    	(currentVal.getElement().equals(qName))) {
      prDbg(fn+"*** Popping back to previous parser");
      try {
	currentVal.close(false);
	currentVal = (Validator)valStack.pop();
	currentVal.skip(loc);
      } catch (IOException ioe) {
	prDbg(fn+"close error:" + ioe);
      }
    }
  }

  public void startPrefixMapping(String prefix, String uri) throws SAXException {
    prDbg("PT: startPrefixMapping: prefix:" + prefix);
    prDbg("PT: \turi:" + uri);
  }

  public void endPrefixMapping(String prefix) throws SAXException {
    prDbg("PT: EndPrefixMapping:" + prefix);
  }

  public void skippedEntity(String entity) throws SAXException {
    prDbg("PT: skippedEntity:" + entity);
  }

  public void characters(char[] cbuf, int start, int len) {
    prDbg("PT: Characters:" + new String(cbuf, start, len));
    try {
      currentVal.flush(loc);
    } catch (IOException ioe) {
      prDbg("PT: Flush error:" + ioe);
    }
  }

  public void ignorableWhitespace(char[] cbuf, int start, int len) {
    prDbg("PT: IgnorableWhiteSpace");
  }

  public void processingInstruction(String target, String data)
          throws SAXException {
    
    final String fn = "PT PI: ";
    prDbg(fn+"ProcessingInstruction:" + target + " " + data);
    if (target.toLowerCase().equals("flexml")) {
      ++depth;
      prDbg(fn+"Found FleXML tag!");
      ++depth;
      StringTokenizer st = new StringTokenizer(data);
      while (st.hasMoreTokens()) {
        String piAttr = st.nextToken();
        StringTokenizer st2 = new StringTokenizer(piAttr, "=\" ");
	if (st2.countTokens() != 2) {
	  prDbg(fn+"Malformed PI Attribute: " + piAttr);
	} else {
	  String piaName = st2.nextToken();
	  String piaVal = st2.nextToken();
	  prDbg(fn+piaName + " = " + piaVal);
	  if (piaName.toLowerCase().equals("type")) {
	    if (piaVal.toLowerCase().equals("schemafrag")) {
	      ++depth;
	      prDbg(fn+"*** found schemaFrag PI ***");
	      // next element needs to be saved as "outermost"
	      // element of subdocument
	      spawnParser = true;
	      --depth;
	    }
	  }
	  else if (piaName.toLowerCase().equals("microhint")){
	  	currentHint = piaVal.toLowerCase();
	  	++depth;
	    prDbg(fn+"*** found Oracle hint: " + currentHint + " ***");
	    --depth;	
	}
	
	}
      }
      depth -= 2;
    }

    try {
      currentVal.flush(loc);
    } catch (IOException ioe) {
      prDbg("PT Flush error:" + ioe);
    }
  }

  public void warning(SAXParseException e) throws SAXException {
    prLog("PT Warning:" + e.getMessage());
  }

  public void error(SAXParseException e) throws SAXException {
    prLog("PT Error:" + e.getMessage());
    throw new SAXException(e.getMessage());
  }

  public void fatalError(SAXParseException e) throws SAXException {
    prLog("PT Fatal error" + e.getMessage());
    throw new SAXException(e.getMessage());
  }


}
