package psl.metaparser;

import oracle.xml.parser.schema.*;
import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

import psl.worklets2.wvm.*;
import psl.worklets2.worklets.*;
import psl.codetransfer.*;

import siena.*;

import java.io.*;
import java.net.*;
import java.util.*;

/** Handles the parsing one input XML message.
  * Spawns Validators/SubParsers to validate subcomponents.
  *
  * $Log$
  * Revision 2.3  2001-01-29 04:04:48  png3
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

  WVM wvm = null;
  String moduleName = null;

  // for SmartEventSchema
  XMLSchema se = null;

  Stack valStack = null;
  Validator currentVal = null;
  boolean spawnParser = false;

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
    System.err.println("Classes hath been delivered!");
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
    String seSchema = Metaparser.getSESchema();
    if (debug) dbg.println(fn+"reading in schema " + seSchema); // debug
    try {
      File f = new File(seSchema);
      URL seURL = f.toURL();
      XSDBuilder b = new XSDBuilder();
      se = (XMLSchema)b.build(seURL);
    } catch (Exception e) {
      log.println(fn+"error while building schema");
      log.println(e);
      return;
    }

    SAXParser p = new SAXParser();
    p.setValidationMode(XMLParser.NONVALIDATING);
    p.setContentHandler(this);
    p.setErrorHandler(this);

    if (debug) dbg.println(fn+"creating new validator");  // debug
    try {
      currentVal = new Validator(xml, new PipedWriter(),
      	se, "SEValid" + instNr, debug);
      // initialize outermost depth
      currentVal.setDepth(-1);
      currentVal.setElement(null);

      if (debug) dbg.println(fn+"starting to parse");  // debug
      p.parse(new StringReader(xml));
      currentVal.close(true);

      prDbg(fn+"checking for processor");  // debug
      if (moduleName != null) {
	prDbg(fn+"module "+moduleName+" should be coming");  // debug
        synchronized (_wklArrivals) {
	  if (_wklArrivals.containsKey(requestID)) {
	    prDbg(fn+"worklet had already arrived:"+
	    	(Date)_wklArrivals.get(requestID));
	  } else {
	    Object lockObj = new Object();
	    synchronized (lockObj) {
	      prDbg(fn+"waiting for worklet arrival:" + MPUtil.timestamp());
	      lockObj.wait();
	    }
	    prDbg(fn+"worklet arrived:" + MPUtil.timestamp());
	  }
	}
	// prDbg(fn+"casting to Def");
        // Def d = (Def) Class.forName(moduleName).newInstance();
	// System.out.println("Here it comes...");
	// d.dummy();
      }

    } catch (Exception e) {
      log.println(fn+"Exception during parsing at " + 
      	MPUtil.printLoc(loc));
      log.println(e);
      e.printStackTrace();
      return;
    }
    prDbg(fn+"shutting down wvm");
    wvm.shutdown();
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
    String oracleResp = null;

    prDbg(fn+"StartElement " + MPUtil.printLoc(loc) + ":" + qName);
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

      prDbg(fn+"creating new WVM("+slt.hostname+","+requestID+")");
      wvm = new WVM(this, slt.hostname, requestID);

      Notification n = new Notification();
      n.putAttribute("hostname", slt.hostname);
      n.putAttribute("source", source);
      n.putAttribute("SrcID", slt.SRC_ID);
      n.putAttribute("RequestID", requestID);
      n.putAttribute("type", "query");
      n.putAttribute("query", MPUtil.makeQuery(qName));
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
	// hash entry now has the XML string
	oracleResp = (String)Metaparser.waitList.get(requestID);
	prDbg(fn+"retrieved OResp of:"+oracleResp);
	XMLSchema subSchema = MPUtil.extractSchema(oracleResp);
	moduleName = MPUtil.extractModuleName(oracleResp);
	// we have a new schema.  parse it out, suck it in...
	currentVal = new Validator(xml, new PipedWriter(),
	  subSchema, "SubValid" + instNr, debug, loc);
	currentVal.send("<?xml version='1.0' encoding='UTF-8'?>");
	// mega-hack -- we've already skipped past it...
	currentVal.send("<"+qName+">");
      } catch (Exception e) {
	prLog(fn+"Exception with Oracle communication: " + e);
      }

      prDbg(fn+"*** Saving depth info of depth:" + depth
        + ", targetElement:" + qName);
      currentVal.setDepth(depth);
      currentVal.setElement(qName);
      spawnParser = false;
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
