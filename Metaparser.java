import oracle.xml.parser.schema.*;
import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import java.io.*;
import java.net.*;
import java.util.*;
import siena.*;


public class Metaparser extends DefaultHandler {

  Locator       locator;
  int    depth = 0;
  String spc   = "  ";

  Siena s = null;

  boolean flexMode = false;
  // these two are used to determine if the "subschema" is done
  int targetDepth = -1;
  String targetElement  = null;

  Stack parserStack = null;
  XReader currentXR = null;

  /** smartevent schema */
  XMLSchema se = null;
  /** inner schema fragment.  Should come from Oracle. */
  XMLSchema frag = null;
  // URLs of the above schemas
  URL seURL=null, fragURL=null;

  String xml = null;  // the XML string we're parsing
  

  private void printMsg(String m) {
    for (int i = 0; i < depth; ++i) {
      System.out.print(spc);
    }
    System.out.println(m);
  }

  private String printLoc() {
    return (locator.getLineNumber() + ":" 
    	+ locator.getColumnNumber());
  }

  /** Constructor */
  public Metaparser() {

    parserStack = new Stack();

    // set up Siena
    HierarchicalDispatcher hd = new HierarchicalDispatcher();
    try {
      hd.setReceiver(new TCPPacketReceiver(31337));
    } catch (IOException ioe) {
      printMsg("Unable to set hd receiver:" + ioe);
      return;
    }
    s = hd;

    Filter f1 = new Filter();
    f1.addConstraint("Source", "EventDistiller");
    f1.addConstraint("Type", "DataToMetaParser");
    try {
      s.subscribe(f1, 
	new Notifiable() {
	  public void notify(Notification n) {handleEDNotification(n);}
	  public void notify(Notification[] s) {}
	}
      );
    } catch (SienaException se) {
      se.printStackTrace();
    }

    Filter f2 = new Filter();
    f2.addConstraint("Source", "Oracle");
    f2.addConstraint("Type", "DataToMetaParser");
    try {
      s.subscribe(f2, 
	new Notifiable() {
	  public void notify(Notification n) {handleOracleNotification(n);}
	  public void notify(Notification[] s) {}
	}
      );
    } catch (SienaException se) {
      se.printStackTrace();
    }
  }

  public void handleEDNotification(Notification n) {
    System.out.println("got ED notification");
    AttributeValue av = n.getAttribute("SmartEvent");
    xml = av.stringValue();
    parse();
  }

  public void handleOracleNotification(Notification n) {
    System.out.println("got Oracle notification:" + n);
  }


  // note that isMain and isSub should be connected to the
  // same underlying source.  isSub will be used to create
  // multiple Readers.
  public void parse() {
    SAXParser p = new SAXParser();
    
    p.setValidationMode(XMLParser.NONVALIDATING);
    p.setContentHandler(this);
    p.setErrorHandler(this);

    printMsg("starting to parse");
    try {
      currentXR = new XReader(new StringReader(xml), new PipedOutputStream(),
      	se, "Validator_1");
      p.parse(new ByteArrayInputStream(xml.getBytes()));
      currentXR.close(true);
    } catch (XMLParseException xmlpe) {
      printMsg("XMLParseException during parsing at " +
	printLoc() + ":" + xmlpe.getMessage());
      return;
    } catch (SAXException se) {
      printMsg("SAXException during parsing:" + se.getMessage());
      return;

    } catch (IOException ioe) {
      printMsg("IOException during parsing:" + ioe.getMessage());
      return;
    }
    printMsg("Done parsing");
  }


  public static void main(String args[]) {

    boolean testFile = false;
    XSDBuilder b;
    BufferedReader br;

    if (args.length < 2) {
      System.out.println("Usage:");
      System.out.println("\tMetaparser <schema-file-1> <schema-file-2> [<test-file>]");
      return;
    }

    URL        seURL      = fileToURL(new File(args[0]));
    URL        fragURL    = fileToURL(new File(args[1]));
    if (args.length == 3) {
      URL        xmlURL     = fileToURL(new File(args[2]));
      testFile = true;
    }

    Metaparser mt = new Metaparser();


    try {
      b = new XSDBuilder();
    } catch (XSDException xsde) {
      mt.printMsg("Exception when creating XSDBuilder():" + xsde.getMessage());
      return;
    }

    mt.printMsg("reading in smartevent schema " + args[0]);
    try {
      mt.se = (XMLSchema) b.build(seURL);
    } catch (Exception e) {
      mt.printMsg("Exception when building schema:" + e.getMessage());
      return;
    }
 
    mt.printMsg("reading in fragment schema " + args[1]);
    try {
      mt.frag = (XMLSchema) b.build(fragURL);
    } catch (Exception e) {
      mt.printMsg("Exception when building schema:" + e.getMessage());
      return;
    }

    if (testFile) {
      mt.printMsg("Reading test file " + args[2]);
      StringBuffer sb = new StringBuffer();
      String s = null;
      try {
	BufferedReader tf_br = new BufferedReader(new FileReader(args[2]));
	do {
	  s = tf_br.readLine();
	  sb.append(s);
	} while (s != null);
      } catch (IOException ioe) {
	mt.printMsg("Exception when reading " + args[2] + ":" + ioe);
	return;
      }
      mt.xml = sb.toString();
      mt.parse();
    }
  }
 
  public void setDocumentLocator(Locator locator) {
    printMsg("SetDocumentLocator:");
    this.locator = locator;
  }

  public void startDocument() {
    printMsg("StartDocument");
  }

  public void endDocument() throws SAXException {
    printMsg("EndDocument");
  }

  public void startElement(
          String namespaceURI, String localName, String qName, Attributes atts)
            throws SAXException {

    printMsg("StartElement (" + printLoc() + "):" + qName);
    for (int i = 0; i < atts.getLength(); i++) {
      String aname = atts.getQName(i);
      String type  = atts.getType(i);
      String value = atts.getValue(i);

      printMsg("   " + aname + "(" + type + ")" + "=" + value);
    }
    try {
      currentXR.flush(locator);
    } catch (IOException ioe) {
      printMsg("Flush error:" + ioe);
    }
    if (flexMode) {
      // these should be pushed on to the stack also...
      printMsg("*** Saving depth info of depth:" + depth
        + ", targetElement:" + qName);
      targetDepth = depth;
      targetElement = qName;
      flexMode = false;
    }
    ++depth;
  }

  public void endElement(String namespaceURI, String localName, String qName) 
  	throws SAXException {
    --depth;
    printMsg("EndElement:" + qName);
    try {
      currentXR.flush(locator);
    } catch (IOException ioe) {
      printMsg("Flush error:" + ioe);
    }
    if ((targetDepth == depth) && (targetElement.equals(qName))) {
      printMsg("*** Popping back to previous parser");
      // should be a pop()
      targetDepth = -1;
      targetElement = null;
      try {
	currentXR.close(false);
	currentXR = (XReader)parserStack.pop();
	currentXR.skip(locator);
      } catch (IOException ioe) {
	printMsg("close error:" + ioe);
      }
    }
  }

  public void startPrefixMapping(String prefix, String uri) throws SAXException {
    printMsg("startPrefixMapping: prefix:" + prefix);
    printMsg("\turi:" + uri);
  }

  public void endPrefixMapping(String prefix) throws SAXException {
    printMsg("EndPrefixMapping:" + prefix);
  }

  public void skippedEntity(String entity) throws SAXException {
    printMsg("skippedEntity:" + entity);
  }

  public void characters(char[] cbuf, int start, int len) {
    printMsg("Characters:" + new String(cbuf, start, len));
    try {
      currentXR.flush(locator);
    } catch (IOException ioe) {
      printMsg("Flush error:" + ioe);
    }
  }

  public void ignorableWhitespace(char[] cbuf, int start, int len) {
    printMsg("IgnorableWhiteSpace");
  }

  public void processingInstruction(String target, String data)
          throws SAXException {
    printMsg("ProcessingInstruction:" + target + " " + data);
    if (target.toLowerCase().equals("flexml")) {
      ++depth;
      printMsg("Found FleXML tag!");
      ++depth;
      StringTokenizer st = new StringTokenizer(data);
      while (st.hasMoreTokens()) {
        String piAttr = st.nextToken();
        StringTokenizer st2 = new StringTokenizer(piAttr, "=\" ");
	if (st2.countTokens() != 2) {
	  printMsg("Malformed PI Attribute: " + piAttr);
	} else {
	  String piaName = st2.nextToken();
	  String piaVal = st2.nextToken();
	  printMsg(piaName + " = " + piaVal);
	  if (piaName.toLowerCase().equals("type")) {
	    if (piaVal.toLowerCase().equals("schemafrag")) {
	      ++depth;
	      printMsg("*** found schemaFrag PI ***");
	      // next element needs to be saved as "outermost"
	      // element of subdocument
	      printMsg("*** pushing currentXR");
	      parserStack.push(currentXR);
	      try {
		currentXR = new XReader(new StringReader(xml), 
		  new PipedOutputStream(), frag, "Validator_2", locator);
		currentXR.send("<?xml version='1.0' encoding='UTF-8'?>");
	      } catch (IOException ioe) {
	        printMsg("XReader creation error: " + ioe);
	      }
	      flexMode = true;
	      --depth;
	    }
	  }
	}
      }
      depth -= 2;
    }

    try {
      currentXR.flush(locator);
    } catch (IOException ioe) {
      printMsg("Flush error:" + ioe);
    }
  }

  public void warning(SAXParseException e) throws SAXException {
    printMsg("Warning:" + e.getMessage());
  }

  public void error(SAXParseException e) throws SAXException {
    throw new SAXException(e.getMessage());
  }

  public void fatalError(SAXParseException e) throws SAXException {
    printMsg("Fatal error");
    throw new SAXException(e.getMessage());
  }

  static URL fileToURL(File file) {

    String path = file.getAbsolutePath();
    String fSep = System.getProperty("file.separator");

    if ((fSep != null) && (fSep.length() == 1)) {
      path = path.replace(fSep.charAt(0), '/');
    }
    if ((path.length() > 0) && (path.charAt(0) != '/')) {
      path = '/' + path;
    }
    try {
      return new URL("file", null, path);
    } catch (java.net.MalformedURLException e) {
      throw new Error("unexpected MalformedURLException");
    }
  }
}
