package psl.metaparser;

import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

/**
 * This class is an implementation of the org.xml.sax.ErrorHandler interface.
 * It will print out user-friendly information when error and warning occur.
 * It purely facilitates the debugging process.
 * 
 * @author Jing Fan
 * @version 0.9
 */
public class MetaparserErrorHandler implements ErrorHandler {
    
    /** Deals with warnings. */
    public void warning ( SAXParseException saxpe )
	throws SAXException {
	System.err.println ( "**Parsing Warning**\n" +
			     " Line:      " +
			     saxpe.getLineNumber () + "\n" +
			     " URI:       " +
			     saxpe.getSystemId () + "\n" +
			     " Message:   " +
			     saxpe.getMessage () );
	throw ( new SAXException ( "Warning encountered" ) );
    }
    
    /** Deals with errors. */
    public void error ( SAXParseException saxpe )
	throws SAXException {
	System.err.println ( "**Parsing Error**\n" +
			     " Line:      " +
			     saxpe.getLineNumber () + "\n" +
			     " URI:       " +
			     saxpe.getSystemId () + "\n" +
			     " Message:   " +
			     saxpe.getMessage () );
	throw ( new SAXException ( "Error encountered" ) );
    }
    
    /** Deals with fatal errors. */
    public void fatalError ( SAXParseException saxpe )
	throws SAXException {
	System.err.println ( "**Parsing Fatal Error**\n" +
			     " Line:      " +
			     saxpe.getLineNumber () + "\n" +
			     " URI:       " +
			     saxpe.getSystemId () + "\n" +
			     " Message:   " +
			     saxpe.getMessage () );
	throw ( new SAXException ( "Fatal Error encountered" ) );
    }
    
}
