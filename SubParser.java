import oracle.xml.parser.schema.*;
import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import java.io.*;
import java.net.*;
import java.util.*;


public class SubParser extends DefaultHandler implements Runnable {

  Locator locator;
  int depth = 0;
  static final String spc = "  ";
  PipedReader pis = null;
  XMLSchema schema = null;
  String instance = "";

  SubParser(PipedWriter pos, XMLSchema s, String inst) 
  	throws IOException {
    instance = inst;
    schema = s;
    try {
      pis = new PipedReader(pos);
    } catch (IOException ioe) {
      printMsg("Error creating PipedReader:" + ioe);
      throw ioe;
    }
  }

  public void printMsg(String m) {
    for (int i = 0; i < depth; ++i) {
      System.err.print(spc);
    }
    System.err.println(instance + ": " + m);
  }

  public String printLoc() {
    return (locator.getLineNumber() + ":" 
    	+ locator.getColumnNumber());
  }

  public void run() {

    SAXParser p = new SAXParser();
    p.setValidationMode(XMLParser.SCHEMA_VALIDATION);
    p.setContentHandler(this);
    p.setErrorHandler(this);
    p.setXMLSchema(schema);

    printMsg("starting to parse");
    try {
      p.parse(pis);
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
    ++depth;
  }

  public void endElement(String namespaceURI, String localName, String qName) 
  	throws SAXException {
    --depth;
    printMsg("EndElement:" + qName);
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
        StringTokenizer st2 = new StringTokenizer(piAttr, "= \"");
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
	      --depth;
	    }
	  }
	}
      }
      depth -= 2;
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
