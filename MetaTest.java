import oracle.xml.parser.schema.*;
import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import java.io.*;
import java.net.*;
import java.util.*;


public class MetaTest extends DefaultHandler {

  Locator       locator;
  int    depth = 0;
  String spc   = "  ";
  String fname = null;

  boolean flexMode = false;
  // these two are used to determine if the "subschema" is done
  int targetDepth = -1;
  String targetElement  = null;

  Stack parserStack = null;
  XReader currentXR = null;
  XMLSchema s1 = null, s2 = null;
  

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


  public static void main(String args[]) {

    if (args.length != 3) {
      System.out.println("Usage:");
      System.out.println("\tMetaTest <xml-file> <schema-file-1> <schema-file-2>");
      return;
    }

    URL       xmlURL      = fileToURL(new File(args[0]));
    URL        s1URL      = fileToURL(new File(args[1]));
    URL        s2URL      = fileToURL(new File(args[2]));
    SAXParser  p          = new SAXParser();
    XSDBuilder b;

    MetaTest mt = new MetaTest();
    mt.fname = args[0];

    BufferedReader br;
    mt.parserStack = new Stack();

    try {
      b = new XSDBuilder();
    } catch (XSDException xsde) {
      mt.printMsg("Exception when creating XSDBuilder():" + xsde.getMessage());
      return;
    }

    mt.printMsg("reading in schema " + args[1]);
    try {
      mt.s1 = (XMLSchema) b.build(s1URL);
    } catch (Exception e) {
      mt.printMsg("Exception when building schema:" + e.getMessage());
      return;
    }
 
    mt.printMsg("reading in schema " + args[2]);
    try {
      mt.s2 = (XMLSchema) b.build(s2URL);
    } catch (Exception e) {
      mt.printMsg("Exception when building schema:" + e.getMessage());
      return;
    }
 
    p.setValidationMode(XMLParser.NONVALIDATING);
    p.setContentHandler(mt);
    p.setErrorHandler(mt);

    mt.printMsg("starting to parse " + mt.fname);
    try {
      mt.currentXR = new XReader(new FileReader(mt.fname), new PipedOutputStream(),
      	mt.s1, "Validator_1");
      p.parse(xmlURL);
      mt.currentXR.close(true);
    } catch (XMLParseException xmlpe) {
      mt.printMsg("XMLParseException during parsing at " +
	mt.printLoc() + ":" + xmlpe.getMessage());
      return;
    } catch (SAXException se) {
      mt.printMsg("SAXException during parsing:" + se.getMessage());
      return;

    } catch (IOException ioe) {
      mt.printMsg("IOException during parsing:" + ioe.getMessage());
      return;
    }
    mt.printMsg("Done parsing " + mt.fname);
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
		currentXR = new XReader(new FileReader(fname), 
		  new PipedOutputStream(), s2, "Validator_2", locator);
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
