package psl.metaparser;

import org.xml.sax.*;
import org.xml.sax.helpers.*;
import org.apache.xerces.parsers.*;
import java.io.*;
import java.net.*;
import java.util.*;

/** Validating subordinate parser thread.
  *
  * $Log$
  * Revision 2.4  2001-01-30 10:16:55  png3
  * Almost working...
  *
  * Revision 2.3  2001/01/29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.2  2001/01/28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
public class SubParser extends DefaultHandler implements Runnable {

  Locator loc;
  int depth = 0;
  static final String spc = "  ";
  PipedReader pr = null;
  // XMLSchema schema = null;
  String inst = "";
  // parent
  Validator v = null;

  SubParser(PipedWriter pw, String inst, 
  	Validator v) throws IOException {
    
    final String fn = inst+"_SP_ctor: ";

    this.inst = inst;
    // schema = s;
    this.v = v;
    try {
      pr = new PipedReader(pw);
    } catch (IOException ioe) {
      v.prLog(fn+"Error creating PipedReader:" + ioe);
      throw ioe;
    }
  }

  public void printMsg(String m) {
    for (int i = 0; i < depth; ++i) {
      System.err.print(spc);
    }
    System.err.println(inst + ": " + m);
  }

  public void run() {

    final String fn = inst+"_SP_run: ";

    SAXParser p = new SAXParser();
    try {
      p.setFeature("http://xml.org/sax/features/validation", true);
      p.setFeature("http://xml.org/sax/features/namespaces", true);
      p.setFeature("http://apache.org/xml/features/validation/schema", true);
    } catch (SAXNotSupportedException snse) {
      v.prLog(fn+"Feature not supported:" + snse.getMessage());
      return;
     } catch (SAXNotRecognizedException snre) {
      v.prLog(fn+"Exception setting feature:" + snre.getMessage());
      return;
    }
    p.setContentHandler(this);
    p.setErrorHandler(this);

    v.prDbg(fn+"starting to parse");
    try {
      p.parse(new InputSource(pr));
    } catch (Exception e) {
      v.prLog(fn+"Exception during parsing:" + e.getMessage());
      return;
    }
    v.prDbg(fn+"Done parsing");
  }

  public void setDocumentLocator(Locator loc) {

    final String fn = inst+"_SP_setDocLoc: ";

    v.prDbg(fn+"SetDocumentLocator:");
    this.loc = loc;
  }

  public void startDocument() {

    final String fn = inst+"_SP_startDoc: ";

    v.prDbg(fn+"StartDocument");
  }

  public void endDocument() throws SAXException {

    final String fn = inst+"_SP_endDoc: ";

    v.prDbg(fn+"EndDocument");
  }

  public void startElement(
          String namespaceURI, String localName, String qName, Attributes atts)
            throws SAXException {

    final String fn = inst+"_SP_startElm: ";

    v.prDbg(fn+"StartElement (" + MPUtil.printLoc(loc) + "):" + qName);
    for (int i = 0; i < atts.getLength(); i++) {
      String aname = atts.getQName(i);
      String type  = atts.getType(i);
      String value = atts.getValue(i);

      v.prDbg(fn+"   " + aname + "(" + type + ")" + "=" + value);
    }
    ++depth;
  }

  public void endElement(String namespaceURI, String localName, String qName) 
  	throws SAXException {

    final String fn = inst+"_SP_endElm: ";

    --depth;
    v.prDbg(fn+"EndElement:" + qName);
  }

  public void startPrefixMapping(String prefix, String uri) throws SAXException {

    final String fn = inst+"_SP_startPM: ";

    v.prDbg(fn+"startPrefixMapping: prefix:" + prefix);
    v.prDbg(fn+"\turi:" + uri);
  }

  public void endPrefixMapping(String prefix) throws SAXException {

    final String fn = inst+"_SP_endPM: ";

    v.prDbg(fn+"EndPrefixMapping:" + prefix);
  }

  public void skippedEntity(String entity) throws SAXException {

    final String fn = inst+"_SP_skippedEntity: ";

    v.prDbg(fn+"skippedEntity:" + entity);
  }

  public void characters(char[] cbuf, int start, int len) {

    final String fn = inst+"_SP_CData: ";

    v.prDbg(fn+"Characters:" + new String(cbuf, start, len));
  }

  public void ignorableWhitespace(char[] cbuf, int start, int len) {

    final String fn = inst+"_SP_WS: ";

    v.prDbg(fn+"IgnorableWhiteSpace");
  }

  public void processingInstruction(String target, String data)
          throws SAXException {

    final String fn = inst+"_SP_PI: ";

    v.prDbg(fn+"ProcessingInstruction:" + target + " " + data);
    if (target.toLowerCase().equals("flexml")) {
      ++depth;
      v.prDbg(fn+"Found FleXML tag!");
      ++depth;
      StringTokenizer st = new StringTokenizer(data);
      while (st.hasMoreTokens()) {
        String piAttr = st.nextToken();
        StringTokenizer st2 = new StringTokenizer(piAttr, "= \"");
	if (st2.countTokens() != 2) {
	  v.prDbg(fn+"Malformed PI Attribute: " + piAttr);
	} else {
	  String piaName = st2.nextToken();
	  String piaVal = st2.nextToken();
	  printMsg(piaName + " = " + piaVal);
	  if (piaName.toLowerCase().equals("type")) {
	    if (piaVal.toLowerCase().equals("schemafrag")) {
	      ++depth;
	      v.prDbg(fn+"*** found schemaFrag PI ***");
	      --depth;
	    }
	  }
	}
      }
      depth -= 2;
    }

  }

  public void warning(SAXParseException e) throws SAXException {

    final String fn = inst+"_SP_warning: ";

    v.prLog(fn+"Warning:" + e.getMessage());
  }

  public void error(SAXParseException e) throws SAXException {

    final String fn = inst+"_SP_error: ";

    throw new SAXException(e.getMessage());
  }

  public void fatalError(SAXParseException e) throws SAXException {

    final String fn = inst+"_SP_fatalError: ";

    v.prLog(fn+"Fatal error");
    throw new SAXException(e.getMessage());
  }

}
