package psl.metaparser;

import java.text.DateFormat;
import java.util.*;
import java.io.*;
import java.net.URL;
import java.net.MalformedURLException;
import java.net.HttpURLConnection;
import siena.*;

// import oracle.xml.parser.schema.*;
// import oracle.xml.parser.v2.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

/** Various static utility methods for metaparser.
  *
  * $Log$
  * Revision 2.6  2001-11-14 04:43:55  valetto
  * Deals with the new micro Oracle; handles remote schemas and tagproceesors via URLs.
  * Also, substantially cleaned up code.
  *
  * Revision 2.5  2001/04/18 19:49:50  png3
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
 
  public static String extractModuleNameFromEvent (Notification n) {
  		AttributeValue attr = n.getAttribute("TPModule");
  		return attr.stringValue();
	}

	public static String extractSchemaURLFromEvent (Notification n) {
		String schemaURLValue;
		AttributeValue attr = n.getAttribute("Value");
    	schemaURLValue = attr.stringValue();
    	return schemaURLValue;
	}
	 
}
