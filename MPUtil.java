package psl.metaparser;

import java.text.DateFormat;
import java.util.*;
import java.io.*;
import java.net.URL;

// import oracle.xml.parser.schema.*;
// import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

/** Various static utility methods for metaparser.
  *
  * $Log$
  * Revision 2.5  2001-04-18 19:49:50  png3
  * modified synchronization method for worklet arrival.  I thought incorrectly
  * that wait()-ing on an object released _all_ of its locks
  *
  * Revision 2.4  2001/02/05 06:35:16  png3
  * Post California version
  *
  * Revision 2.3  2001/01/30 10:16:55  png3
  * Almost working...
  *
  * Revision 2.2  2001/01/29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.1  2001/01/28 17:52:17  png3
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
    final String endTok = "</module>";
    int startIdx = s.indexOf(startTag);
    startIdx = s.indexOf(">", startIdx);
    int endIdx = s.indexOf(endTok, startIdx);
    String result = s.substring(startIdx + 1, endIdx);
    System.err.println(fn+"Expected Module Name:\n" + result);
    return result;
  }

  /** pulls subschema out of oracle response XML */
  // TODO: integrate with other logging...
  public static void extractSchema(String s) {
    final String fn = "MPU_extractSchema: ";
    final String startTag = "<subschema>";
    final String endTag = "</subschema>";
    int startIdx = s.indexOf(startTag)+startTag.length();
    int endIdx = s.indexOf(endTag, startIdx);
    String result = s.substring(startIdx, endIdx);
    System.err.println(fn+"extracted schema String:\n" + result);

    // StringReader sr = new StringReader(result);
    // XMLSchema schema = null;
    try {
      FileWriter schema = new FileWriter("schema.xsd");
      schema.write(result);
      schema.close();
      // URL base = new URL("http://www.w3.org/1999/XMLSchema-instance");
      // XSDBuilder b = new XSDBuilder();
      // schema = (XMLSchema)b.build(sr, base);
    } catch (Exception e) {
      System.err.println(fn+"error while building schema");
      System.err.println(e);
      return;
    }
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
