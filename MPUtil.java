import java.text.DateFormat;
import java.util.*;
import java.io.*;
import java.net.URL;

import oracle.xml.parser.schema.*;
import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

/** Various static utility methods for metaparser.
  *
  * $Log$
  * Revision 2.1  2001-01-28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
class MPUtil {

  /** Generate a timestamp string */
  public static String timestamp() {
    final DateFormat df = 
    	DateFormat.getTimeInstance(DateFormat.MEDIUM);
    return df.format(new Date());
  }

  public static String makeQuery(String elm) {
    String s = new String("<?xml version=\"1.0\"?>");
    s += "<schemaQuery version=\"1.0\" name=\""+ elm+ "\">";
    s += "<xpath>/" + elm + "</xpath>";
    s += "</schemaQuery>";
    return s;
  }

  public static String printLoc(Locator l) {
    return ("(" + l.getLineNumber() + ":" 
    	+ l.getColumnNumber() + ")");
  }

  /** pulls module name out of oracle response XML */
  // TODO: integrate with other logging...
  public static String extractModuleName(String s) {
    final String fn = "MPU_extractModuleName: ";
    final String startTag = "<module";
    final String endTok = ".";
    int startIdx = s.indexOf(startTag);
    startIdx = s.indexOf(">", startIdx);
    int endIdx = s.indexOf(endTok, startIdx);
    String result = s.substring(startIdx + 1, endIdx);
    System.err.println(fn+"Extracted Module:\n" + result);
    return result;
  }

  /** pulls subschema out of oracle response XML */
  // TODO: integrate with other logging...
  public static XMLSchema extractSchema(String s) {
    final String fn = "MPU_extractSchema: ";
    final String startTag = "<subschema>";
    final String endTag = "</subschema>";
    int startIdx = s.indexOf(startTag)+startTag.length();
    int endIdx = s.indexOf(endTag, startIdx);
    String result = s.substring(startIdx, endIdx);
    System.err.println(fn+"extracted schema String:\n" + result);
    StringReader sr = new StringReader(result);
    XMLSchema schema = null;
    try {
      URL base = new URL("http://www.w3.org/1999/XMLSchema-instance");
      XSDBuilder b = new XSDBuilder();
      schema = (XMLSchema)b.build(sr, base);
    } catch (Exception e) {
      System.err.println(fn+"error while building schema");
      System.err.println(e);
      return null;
    }
    return schema;
  }

  // got this from Oracle, but I think it's been superseded
  // by the built-in toURL() method of File
  /*
  static URL fileToURL(String fname) {

    File file = new File(fname);

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
  */
}
