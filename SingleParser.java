package psl.metaparser;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.FileOutputStream;

import java.util.Vector;
import java.util.Stack;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.swing.tree.DefaultMutableTreeNode;

import org.xml.sax.ContentHandler;
import org.xml.sax.Locator;
import org.xml.sax.SAXException;
import org.xml.sax.Attributes;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.XMLReaderFactory;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;

import org.jdom.Attribute;
import org.jdom.Comment;
import org.jdom.DocType;
import org.jdom.Document;
import org.jdom.Element;
import org.jdom.JDOMException;
import org.jdom.Namespace;
import org.jdom.ProcessingInstruction;
import org.jdom.input.SAXBuilder;
import org.jdom.output.XMLOutputter;

import psl.oracle.impl.IOracle;
import psl.oracle.impl.SchemaFragment;

import psl.wgcache.impl.Cacheable;
import psl.wgcache.impl.PersonalCacheModuleImpl;

/**
 * This class makes the propertis of FleXML possible.<br/>
 * <p>It implements the org.xml.sax.Contenthandler interface to allow the 
 * stream property of FleXML.</p>
 * <p>It will pause the parsing process when hit an unknown tag; and it will
 * query the Oracle for necessary schema fragment(s) before going on.</p>
 * <p>It will call corresponding modules both before and after each FleXML 
 * block reaches. (This function will be added as soon as the interface of
 * modules is determined.)</p>
 * <p>Each SingleParser runs a separate thread to allow multiply instances
 * for different sources.</p>
 * <p> It will optionally output the whole source smart event into a file 
 * with name "srcID_output.xml".</p>
 * <p> It will optionally generate a JDOM tree for the whole smart event for
 * further manipulation.</p>
 * 
 * @author Jing Fan
 * @version 0.9
 */
class SingleParser implements ContentHandler, Runnable {
    /** Name of the default parser to be used. */
    public static final String DEFAULT_PARSER_NAME =
        "org.apache.xerces.parsers.SAXParser";
    
    private static final String DEFAULT_CACHE_SERVICE_ROLE_NAME =
	"psl.metaparser.MetaparserCacheServiceRole";

    private long srcID;
    private StringBuffer allContents;
    private Stack stack;
    private int index;

    private Document output; // Output JDOM
    private Element current; // The current element being working on
    
    private boolean generateOutput;
    private boolean generateTree;
    private DefaultMutableTreeNode root; // Root of output JTree
    private DefaultMutableTreeNode currentNode; // Current node

    private Metaparser mp;
    private XMLReader parser; 
    private Locator locator;
    private FleXMLReader reader;
    
    private FileWriter fw = null;
    private PrintWriter pw = null;

    private Vector currentPrefixMapping;
    private int level;
    private String path;

    private boolean isWaitingForReply;
    private String waitingTag;
    private SchemaFragment currentReply;

    private PersonalCacheModuleImpl cache;
    
    private Hashtable modulePool;
    
    private IOracle oracle;

    public SingleParser ( long srcID, Metaparser mp ) {
	this.srcID = srcID;
	this.mp = mp;
	reset ();
    }
    
    private void reset () {
        this.allContents = new StringBuffer ();
	this.stack = new Stack ();
	this.index = 0;
	
	this.output = null;
	this.current = null;
	
	this.generateOutput = false;
	this.generateTree = false;
	this.root = null;
	this.currentNode = null;
	
	this.mp = mp;
	this.locator = null;
	this.reader = new FleXMLReader ( this );
	
	fw = null;
	pw = null;
	
	currentPrefixMapping = new Vector ();
	level = 0;
	path = "";

	isWaitingForReply = false;
	waitingTag = null;
	currentReply = null;
	
	cache = 
	    new PersonalCacheModuleImpl ( DEFAULT_CACHE_SERVICE_ROLE_NAME );
	
	modulePool = new Hashtable ();
	
	oracle = mp.getOracle ();
	
        try {
            parser = XMLReaderFactory.createXMLReader ( DEFAULT_PARSER_NAME );
	    // this.setDestination ( "test.xml" );
	    this.setGenerateOutput ( true );
	    this.setGenerateTree ( true );
            ErrorHandler errorHandler = new MetaparserErrorHandler ();
            parser.setContentHandler ( this );
            parser.setErrorHandler ( errorHandler );
        } catch ( org.xml.sax.SAXException saxe ) {
            appendLog ( "Cannot create parser" );
        }	
    }
    
    StringBuffer getContent () { return this.allContents; }
    
    long getSrcID () { return this.srcID; }

    public Document getDocument () { return this.output; }

    public DefaultMutableTreeNode getTree () {
	if ( !generateTree ) 
	    return null;
	else
	    return root;
    }

    public void run () {

	try {
            parser.parse ( new InputSource ( reader ) );
        } catch ( org.xml.sax.SAXException saxe ) {
            appendLog ( saxe.toString () );
	    saxe.printStackTrace ();
        } catch ( java.io.IOException ioe ) {
            appendLog ( "Cannot read from source" );
        }

    } 

    public void setDestination ( String fileName ) {
	File dest = null;
	try {
	    if ( ( dest = new File (fileName) ).createNewFile () )
		appendLog ( "create file: " + dest.toString () );
	    if ( !( (dest.exists () ) && ( dest.canWrite () ) ) ) {
		appendLog ( "Cannot save file " + fileName );
		return;
	    }
	    fw = new FileWriter( dest.toString () );
	    pw = new PrintWriter ( fw );
	} catch ( IOException ioe ) {
	    appendLog ( "IO Exception" );
	    pw = null;
	}
    }

    public void setGenerateTree ( boolean generateTree ) {
	this.generateTree = generateTree;
    }
    
    public void setGenerateOutput ( boolean generateOutput ) {
	this.generateOutput = generateOutput;
    }
    
    public void setDocumentLocator ( Locator locator ) {
	appendLog ( "  * setDocumentLocator() Called" );
	this.locator = locator;
    }
    
    public void startDocument () throws SAXException {
	appendLog ( "Parsing begins..." );
	this.output = new Document ( new Element ( "Dummy" ) );
	this.current = null;
	if ( generateTree ) {
	    root = new DefaultMutableTreeNode ( "" + srcID );
	    // new TreeViewer ( root );
	    currentNode = root;
	}
    }
    
    public void endDocument () throws SAXException {
	appendLog ( "...Parsing ends." );
	if ( pw != null ) {
	    pw.close ();
	} else
	    appendLog ( "No output" );
	
	if ( generateOutput ) {
	    XMLOutputter outputter = new XMLOutputter ();
	    try {
		outputter.output ( output, 
				   new FileOutputStream ( srcID + 
							  "_output.xml" ) );
	    } catch ( java.io.IOException ioe ) {
		appendLog ( "IO Exception" );
	    }
	}
	if ( generateTree ) {
	    if ( root == null ) 
		appendLog ( "Empty root" );
	    try {
		new TreeViewer ( root );
	    } catch ( Error e ) {
		appendLog ( "To see the output visually, " +
				     "open an X-server." );
	    } catch ( Exception e ) {
		appendLog ( "To see the output visually, " +
                                     "open an X-server." );
            }
	}
	mp.dispatch ( new MetaparserParsedTree ( srcID, root ) );
	suicide ();
    }
    
    public void processingInstruction ( String target, String data ) 
	throws SAXException {
	appendLog ( "PI: Target: " + target + " and Data: " + data );
	if ( pw != null ) {
	    pw.println ( "<?" + target + " " + data + "?>" );
	}
	output.addProcessingInstruction ( target, data );
	if ( generateTree ) {
	    currentNode.add ( new DefaultMutableTreeNode 
		( new String ( "<?" + target + " " + data + "?>" ) ) );
	}
    }
    
    public void startPrefixMapping ( String prefix, String uri ) {
	//appendLog ( "Mapping starts for prefix " + 
	//		     prefix + " mapped to URI " + uri );
	if ( pw != null ) {
	    String temp = "xmlns";
	    if ( prefix.length () != 0 ) 
		temp += ( ":" + prefix );
	    temp += ( "=\"" + uri + "\"" );
	    currentPrefixMapping.add ( temp );
	    // pw.println ( "Start prefix mapping: " + prefix + " -> " + uri );
	}
    }
    
    public void endPrefixMapping ( String prefix ) {
	//appendLog ( "Mapping ends for prefix " + prefix );
	if ( pw != null ) {
	    // pw.println ( "End prefix mapping: " + prefix );
	}
    }
    
    synchronized void setReply ( SchemaFragment reply ) {
	currentReply = reply;
	isWaitingForReply = false;
    }
    
    private void queryTag ( String namespaceURI, String localName )
	throws SAXException {

	// The following will be replaced by a String
	//
	// SchemaFragment newQuery = new SchemaFragment ();
	// newQuery.setSrcID ( this.srcID );
	// if ( !namespaceURI.equals ( "" ) ) 
	//     newQuery.setNameSpace ( namespaceURI );
	// newQuery.setName ( localName );
	// newQuery.setPath ( path );
	
	// Start querying schema information of current tag
	String newKey = new String ( namespaceURI + localName );
	try {
	    Cacheable existingTag = cache.query ( newKey );
	    currentReply = ( SchemaFragment )existingTag.data;
	    return;
	} catch ( java.lang.ClassCastException cce ) {
	    appendLog ( "Unknown error occurred due to class " +
				 "cast exception." );
	    currentReply = null;
	    return;
	} catch ( psl.wgcache.exception.WGCException wgce ) {
	    // No results from cache, so query Oracle instead
	} catch ( java.lang.NullPointerException npe ) {
	    appendLog ( "Cache returns null" );
	}
	
	String newQuery = ( srcID + "," );
	if ( !namespaceURI.equals ( "" ) )
	    newQuery += ( namespaceURI + ":" );
	newQuery += ( localName + "," );
	newQuery += path;
	
	isWaitingForReply = true;
	waitingTag = localName;

	//	mp.queryTag ( newQuery );	
	//	
	//	while ( isWaitingForReply ) {
	//	    try {
	//		Thread.sleep ( 10 );
	//	    } catch ( java.lang.InterruptedException ie ) {
	//		appendLog ( "Interrupted" );
	//	    }
	//	}
	
	try {
	    currentReply = oracle.getFragment ( newQuery );
	} catch ( psl.oracle.exceptions.UnknownTagException ute ) {
	    appendLog ( "Tag Unknown." );
	} catch ( psl.oracle.exceptions.InvalidQueryFormatException iqfe ) {
	    appendLog ( "Invalid Query Format Exception." );
	} catch ( psl.oracle.exceptions.InvalidSchemaFormatException isfe ) {
	    appendLog ( "Invalid Schema Format Exception." );
	}
	
	if ( null == currentReply ||
	     !waitingTag.equals ( currentReply.getName () ) ) {
	    // appendLog ( "Reply doesn't match query" );
	    if ( null == currentReply )
		appendLog ( "Null reply" );
	    else {
		appendLog ( "Waiting Tag: " + waitingTag );
		appendLog ( "Current Reply: " + 
				     currentReply.getName () );
	    }
	    // throw new SAXException ( "Reply doesn't match query" );
	} else {
	    waitingTag = null;
	    Cacheable newData = 
		new Cacheable ( currentReply, newKey, 
				currentReply.toString ().length () );
	    cache.put ( newData );
	}
	
	// End of query, information should be stored in currentReply now.
    }
    
    private IMetaparserModule getModule ( SchemaFragment currentTag ) {
	if ( currentTag == null ) return null;
	
        String moduleName = currentTag.getModuleName ();
        boolean isSingleton = currentTag.getIsSingleton ();
        IMetaparserModule currentModule = null;
        if ( isSingleton ) {
            currentModule = ( IMetaparserModule )modulePool.get ( moduleName );
            if ( null == currentModule ) {
                try {
                    currentModule = 
			( IMetaparserModule )Class.forName ( moduleName )
			.newInstance ();
                    modulePool.put ( moduleName, currentModule );
                } catch ( java.lang.ClassNotFoundException cnfe ) {
                    appendLog ( "Cannot initialize module: " +
                                         moduleName );
		    return null;
                } catch ( java.lang.InstantiationException ie ) {
                    appendLog ( "Cannot initialize module: " +
                                         moduleName );
                    return null;
		} catch ( java.lang.IllegalAccessException iae ) {
                    appendLog ( "Cannot initialize module: " +
                                         moduleName );
                    return null;
		}		    
            }
        } else {
            try {
                currentModule = 
		    ( IMetaparserModule )Class.forName ( moduleName )
		    .newInstance ();
            } catch ( java.lang.ClassNotFoundException cnfe ) {
                appendLog ( "Cannot initialize module: " +
                                     moduleName );
		return null;
            } catch ( java.lang.InstantiationException ie ) {
		appendLog ( "Cannot initialize module: " +
				     moduleName );
		return null;
	    } catch ( java.lang.IllegalAccessException iae ) {
		appendLog ( "Cannot initialize module: " +
				     moduleName );
		return null;
	    }
        }	
	return currentModule;
    }
    
    public void startElement ( String namespaceURI,
			       String localName,
			       String rawName,
			       Attributes atts )
	throws SAXException {

        path += ( "\\" + localName );
	
	queryTag ( namespaceURI, localName );

	/*
	if ( null == currentReply ) 
	    throw ( new SAXException ( "Proper schema fragment not found: " +
				       namespaceURI + "/" + localName ) );
	*/
	
	
	if ( currentReply != null ) {
	    // Start validating with the schema fragment 
	    // contained in currentReply
	    appendLog ( "\nParsing with the following Schema Fragment:" );
	    appendLog ( currentReply.toString () + "\n" );
	    appendLog ( "***********************************\n" );
	    // End of validation
	} else {
	    appendLog ( "Proper schema fragment not found: " +
				 namespaceURI + "/" + localName );
	}
    
	// Start calling the correct Module
	IMetaparserModule currentModule = getModule ( currentReply );
	if ( currentModule != null ) {
	    currentModule.tagOpening ( namespaceURI, localName, 
				       rawName, atts );
	    if ( !currentModule.isSingleton () )
		currentModule.destroy ();
	}
	// End of module call
		
	
	// Start parsing
	String temp = "";
	String tempNode = "";
	appendLog ( "startElement: " + localName );
	if ( pw != null ) {
	    for ( int i = 0; i < level; i ++ )
		pw.print ( "  " );
	    level ++;
	}
	temp = "<" + rawName;
	if ( generateTree ) 
	    tempNode += temp;
        if ( pw != null )
	    pw.print ( temp );
	allContents.append ( temp );
	Element newElement = new Element ( localName, namespaceURI );
	if ( null == current ) {
	    output.setRootElement ( newElement );
	} else {
	    current.addChild ( newElement );
	}
	current = newElement;
	stack.push ( new MetaparserTag ( newElement, index ) );
	index += temp.length ();
	
	if ( currentPrefixMapping.size () != 0 ) {
	    for ( int i = 0; i < currentPrefixMapping.size (); i ++ ) {
		temp = " " + ( ( String )currentPrefixMapping.get ( i ) );
		if ( generateTree )
		    tempNode += temp;
		if ( pw != null )
		    pw.print ( temp );
		allContents.append ( temp );
		index += temp.length ();
	    }
	    currentPrefixMapping = new Vector ();
	}
	
	/*
	if ( !namespaceURI.equals ( "" ) ) {
	    appendLog ( " in namespace " + 
				 namespaceURI + " (" + rawName + ")" );
	} else {
	    appendLog ( " has no associated namespace." );
	}
	*/
	
	for  ( int i = 0; i < atts.getLength (); i ++ ) {
	    /*
	      appendLog ( "Attributes: " + atts.getLocalName ( i ) + 
	      "*" + atts.getValue ( i ) );
	    */
	    temp = ( " " + atts.getRawName ( i ) + "=\"" + 
		     atts.getValue ( i ) + "\"" );
	    if ( generateTree )
		tempNode += temp;
	    if ( pw != null )
		pw.print ( temp );
	    allContents.append ( temp );
	    index += temp.length ();
	    current.addAttribute ( atts.getRawName ( i ), 
				   atts.getValue ( i ) );
	}
	
	temp = ">";
	if ( generateTree )
	    tempNode += temp;
        if ( pw != null )
	    pw.println ( temp );
	allContents.append ( temp );
	index += temp.length ();

	current.addAttribute ( "parsingStatus", "parsing" );
	if ( generateTree ) {
	    DefaultMutableTreeNode child = 
		new DefaultMutableTreeNode ( tempNode );
	    currentNode.add ( child );
	    currentNode = child;
	}
	// End of parsing
	
	currentReply = null; // Reset currentReply for next tag
    }
    
    public void endElement ( String namespaceURI, 
			     String localName, 
			     String rawName )
	throws SAXException {
	
	
	appendLog ( "endElement: " + localName + "\n" );
	path = path.substring ( 0, path.length () - localName.length () - 1 );

        queryTag ( namespaceURI, localName );

	/*
        if ( null == currentReply )
            throw ( new SAXException ( "Proper schema fragment not found: " +
                                       namespaceURI + "\\" + localName ) );
	*/
	

	String temp = "";
	if ( pw != null ) {
	    level --;
	    for ( int i = 0; i < level; i ++ )
		pw.print ( "  " );
	}
	temp = ( "</" + rawName + ">\n" );
	if ( pw != null )
	    pw.print ( temp );
	allContents.append ( temp );
	index += temp.length ();

	MetaparserTag currentTag = ( MetaparserTag )stack.pop ();
	try {
	    current.getAttribute ( "parsingStatus" ).setValue ( "parsed" );
	} catch ( org.jdom.NoSuchAttributeException nsae ) {
	}
	
	try {
	    String chunk = 
		allContents.substring ( currentTag.getStartIndex (),
					index );
	    appendLog ( "Parsing:\n" + chunk );
	    try {
		// validating current chunk
		if ( validate ( chunk ) ) {
		    current.removeAttribute ( "parsingStatus" );

		    // Start calling the correct Module
		    IMetaparserModule currentModule = 
			getModule ( currentReply );
		    if ( currentModule != null ) {
			currentModule.tagClosing ( namespaceURI, localName,
						   rawName, true, current );
			if ( !currentModule.isSingleton () )
			    currentModule.destroy ();
		    }
		    // End of module call		    

		} else {
		    current.getAttribute ( "parsingStatus" )
			.setValue ( "INVALID" );

		    // Start calling the correct Module
		    IMetaparserModule currentModule = 
			getModule ( currentReply );
		    if ( currentModule != null ) {
			currentModule.tagClosing ( namespaceURI, localName,
						   rawName, false, current );
			if ( !currentModule.isSingleton () )
			    currentModule.destroy ();
		    }
		    // End of module call

		}
	    } catch ( org.jdom.NoSuchAttributeException nsae ) {
	    }
	} catch ( StringIndexOutOfBoundsException sioobe ) {
	    appendLog ( "String Index Out of Bounds" );
	}
	if ( stack.empty () )
	    current = null;
	else
	    current = ( ( MetaparserTag )stack.peek () ).getContent ();
	if ( currentTag.getContent ().getName ().equals ( localName ) &&
	     currentTag.getContent ().getNamespaceURI ()
	     .equals ( namespaceURI ) ) {
	    appendLog ( "***********************************\n" );
	    Vector data = currentTag.getData ();
	    int count = data.size ();
	    for ( int i = 0; i < count; i ++ ) {
		MetaparserTag.Data currentData = 
		    ( MetaparserTag.Data )data.get ( i );
		allContents.delete ( currentData.getStartIndex (),
				     currentData.getStartIndex () +
				     currentData.getLength () );
		index -= currentData.getLength ();
	    }
	    currentTag.removeData ();
	} else {
	    appendLog ( "Error nested tag: " + rawName );
	    appendLog ( currentTag.getTagName () );
	}
	if ( generateTree ) {
	    try {
		currentNode = 
		    ( DefaultMutableTreeNode ) currentNode.getParent ();
	    } catch ( java.lang.NullPointerException npe ) {
		currentNode = null;
	    }
	}
	
	currentReply = null; // Reset currentReply for next tag
    }
    
    public void characters ( char[] ch, int start, int end )
	throws SAXException {
	String s = 
	    ( new String ( ch, start, end ) ).replace ( '\n', ' ' ).trim ();
	//appendLog ( "characters: " + s );
	
	if (  ( pw != null ) && ( s.length () != 0 ) )
	    for ( int i = 0; i < level; i ++ )
		pw.print ( "  " );
	if ( s.length () != 0 ) {
	    s += "\n";
	    allContents.append ( s );
	    if ( pw != null )
		pw.print ( s );
	    MetaparserTag currentTag = ( MetaparserTag )stack.peek ();
	    if ( currentTag != null ) 
		currentTag.addData ( index, s.length () );
	    current.addChild ( s );
	    index += s.length ();
	    if ( generateTree ) {
		currentNode.add ( new DefaultMutableTreeNode ( s.trim() ) );
	    }
	}
    }
    
    public void ignorableWhitespace ( char[] ch, int start, int end )
	throws SAXException {
	String s = new String ( ch, start, end );
	//appendLog ( "ignorableWhitespace: [" + s + "]" );
	//if (  ( pw != null ) && ( s.trim ().length () != 0 ) )
	//  pw.print ( s );
    }
    
    public void skippedEntity ( String name ) throws SAXException {
	//appendLog ( "skippedEntity: " + name );
	if ( pw != null )
	    pw.print ( "&" + name + ";" );
    }

    private boolean validate ( String in ) {
	return false;
    }

    void processSmartEvent ( String newEvent ) {
	reader.append ( newEvent );
    }
    
    void closeStream () {
	reader.close ();
    }
    
    private synchronized void suicide () {
	this.reset ();
	mp.killSingleParser ( this.srcID );
    }

    private synchronized void appendLog ( String newLog ) {
	mp.appendLog ( this.srcID + ": " + newLog );
    }

    /**
     * This inner class creates a reader for the standard XML parser that
     * allows adding data dynamically, so that smart event can come in 
     * piece by piece.<br/>
     * 
     * Further development is needed to deal with time-out cases when expected
     * inputs don't arrive within a given period of time.
     *
     * @author Jing Fan
     * @version 0.9
     */
    static int MIN_CHUNK_SIZE = 1024;
    static int count = 0;
    private class FleXMLReader extends java.io.Reader {
    
	private boolean closed = false;
	
	private SingleParser parser;
	private StringBuffer str;
	private int length;
	private int next;
	
	/**
	 * Create a new string reader.
	 *
	 * @param s  String providing the character stream.
	 */
	public FleXMLReader ( SingleParser parser ) {
	    this.closed = false;
	    this.parser = parser;
	    this.str = new StringBuffer ();
	    this.length = this.str.length ();
	    this.next = 0;
	}
	
	/** Check to make sure that the stream has not been closed */
	private void ensureOpen() throws IOException {
	    if ( null == str )
		throw new IOException("Stream closed");
	}
	
	/**
	 * Read a single character.
	 *
	 * @return     The character read, or -1 if the end of the stream 
	 *             has been reached
	 *
	 * @exception  IOException  If an I/O error occurs
	 */
	public int read () throws IOException {
	    synchronized (lock) {
		ensureOpen();
		
		if ( ( this.closed ) && ( next < length ) ) {
		     int result = ( int )str.charAt ( next );
		     str.deleteCharAt ( next );
		     length --;
		     return result;
		}
		
		while ( ( next >= length ) && ( !this.closed ) )
		    Thread.yield ();
		if ( next < length ) {
		    int result = ( int )str.charAt ( next );
		    str.deleteCharAt ( next );
		    length --;
		    return result;
                } else 
		    return -1;
	    }
	}
	
	/**
	 * Read characters into a portion of an array.
	 *
	 * @param      cbuf  Destination buffer
	 * @param      off   Offset at which to start writing characters
	 * @param      len   Maximum number of characters to read
	 *
	 * @return     The number of characters read, or -1 if the end of the
	 *             stream has been reached
	 *
	 * @exception  IOException  If an I/O error occurs
	 */
	public int read ( char cbuf[], int off, int len ) throws IOException {
	    synchronized ( lock ) {
		ensureOpen();
		if ( ( off < 0 ) || ( off > cbuf.length ) || ( len < 0 ) ||
		     ( ( off + len ) > cbuf.length ) || 
		     ( ( off + len ) < 0 ) ) {
		    throw new IndexOutOfBoundsException();
		} else if ( len == 0 ) {
		    return 0;
		}
		while ( ( next >= length ) && ( !this.closed ) )
		    Thread.yield ();
		if ( ( next >= length ) && ( this.closed ) ) {
		    return -1;
		}
		while ( ( ( length - next ) < len ) && 
			( ( length - next ) < MIN_CHUNK_SIZE ) &&
			( !this.closed ) )
		    Thread.yield ();
		
		int n = Math.min( length - next, len );
		
		str.getChars( next, next + n, cbuf, off );
		str.delete ( next, next + n );
		length -= n;
		return n;
	    }
	}
	
	/**
	 * Tell whether this stream is ready to be read.
	 *
	 * @return True if the next read() is guaranteed not to block for input
	 *
	 * @exception  IOException  If the stream is closed
	 */
	public boolean ready() throws IOException {
	    synchronized (lock) {
		ensureOpen();
		return true;
	    }
	}
	
	/**
	 * Tell whether this stream supports the mark() operation.
	 */
	public boolean markSupported() {
	    return false;
	}
	
	/**
	 * Close the stream.
	 */
	public void close() {
	    closed = true;
	}
       
	public void append ( String newStr ) {
	    if ( ( count ++ ) % 2 != 0 ) 
		return;
	    str.append ( newStr );
	    length = str.length ();
	}
    }
}   




