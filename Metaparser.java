package psl.metaparser;

import psl.util.*;

import psl.oracle.*;
import psl.oracle.impl.*;
import psl.oracle.impl.SchemaFragment;

import psl.groupspace.*;
import psl.groupspace.impl.*;

import org.jdom.Document;
import org.jdom.Element;
import org.jdom.input.SAXBuilder;

import java.util.Hashtable;

import java.io.StringReader;



/** 
 * Metaparser provides a metaparser to parse smart events written
 * in FleXML. It can handle smart event from different sources
 * and create several SingleParse instances to parse them separately.<br/>
 * 
 * Metaparser also serves as the gateway for all SingleParser instances to
 * communicate with FleXML Schema Oracle through Groupspace Controller.<br/>
 * 
 * @author Jing Fan
 * @version 0.9
 */

public class Metaparser {
     
    // This is an instance of a local that the Mataparser will use to
    // communicate with FleXML Oracle. 
    private GroupspaceController gc;

    // An instance of MetaparserService to send Groupspace Event through
    // GroupspaceController, and to perform callbacks to respond to 
    // Oracle replies.
    private MetaparserService ms;
    
    // This appears here only to simulate a real Oracle service
    // There should be at least one Oracle accessible to allow
    // the Metaparser to function properly.
    private OracleService os;
    
    // This is an instance of a local Oracle that will reply to queries
    // from all SingleParser instances.
    private IOracle oracle;

    // A list of all instances of SingleParser contained within this
    // Metaparser.
    private Hashtable parserList;
    
    // A parser to parse smart event coming through Groupspace Controller.
    private SAXBuilder builder;
    
    /** Default constructor. */
    public Metaparser () {
	// Create a new local Groupspace Controller
	this ( new GroupspaceController () );
    }
    
    /** 
     * Constructor 
     * 
     * @param gc Local GC to be used
     */
    public Metaparser ( GroupspaceController gc ) {
	this.gc = gc;
	String stack[] = null;
	String services[] = { "psl.groupspace.impl.NullService" };
	this.gc.init ( services, stack, new Configuration () );

	ms = new MetaparserService ( this );
	this.gc.addService ( ms );
	
	//	os = new OracleService ();
	//	this.gc.addService ( os );
	
	oracle = new Oracle ();
	parserList = new Hashtable ();
	
	builder = new SAXBuilder ();
	
    }
    
    /**
     * This method sends a query to Oracle through the local GC.
     * 
     * @param newQuery Content of new query.
     */
    public void queryTag ( String newQuery ) {
	System.err.println ( "Sending query" );
	ms.setNewOracleQuery ( newQuery );
	System.err.println ( "Sent" );
	return;
    }
    
    /**
     * Processes the reply from Oracle. It will find the correct 
     * SingleParser instance first and send the reply to that 
     * SingleParser.
     * 
     * @param oracleReply Reply from Oracle.
     */
    public void processOracleReply ( SchemaFragment oracleReply ) {
	long srcID = oracleReply.getSrcID ();
	System.err.println ( "Process reply for source: " + srcID );
	try {
	    SingleParser parser = 
		( SingleParser )parserList.get ( new Long ( srcID ) );
	    parser.setReply ( oracleReply );
	} catch ( NullPointerException npe ) {
	    System.err.println ( "Unwanted reply received" );
	}
	return;
    }
    
    /**
     * Processes a new smart event coming from GC. A correct SingleParser
     * will be found or a new one will be instantiated first before
     * the new smart event is dispatched.
     * 
     * @param newEvent New smart event coming through local GC.
     */
    public synchronized void processSmartEvent ( SmartEvent newEvent ) {
	String input = newEvent.toString ();
	Element event = new Element ( "Dummy" );
	SingleParser parser = null;
	long srcID = -1l;
	
	try {
	    Document temp = builder.build ( new StringReader ( input ) );
	    event = temp.getRootElement ();
	} catch ( org.jdom.JDOMException jdome ) {
	    System.err.println ( "Bad formatted smart event, ignore" );
	    System.err.println ( jdome.toString () );
	    return;
	}
	
	try {
	    srcID = event.getAttribute ( "srcID" ).getLongValue ();
	} catch ( org.jdom.NoSuchAttributeException nsae ) {
            System.err.println ( "Smart event without source, ignore" );
            return;
        } catch ( org.jdom.DataConversionException dce ) {
            System.err.println ( "Error format of source ID, ignore" );
            return;
        }
	
	parser = ( SingleParser )parserList.get ( new Long ( srcID ) );
	if ( null == parser ) {
	    // Create a new parser to parse smart event from this source
	    System.err.println ( "Create new parser" );
	    parser = new SingleParser ( srcID, this );
	    parserList.put ( new Long ( srcID ), parser );
	    new Thread ( parser ).start ();
	}

	String content = event.getContent();
	if ( content.length () > 0 ) {
	    parser.processSmartEvent ( content );
	} else 
	    System.err.println ( "Warning: Empty smart event" );
	
	try {
	    boolean finished = 
		event.getAttribute ( "finished" ).getBooleanValue ();
	    if ( finished ) 
		parser.closeStream ();
	} catch ( org.jdom.NoSuchAttributeException nsae ) {
	    // Do nothing, assume false as default value
	} catch ( org.jdom.DataConversionException dce ) {
	    System.err.println ( "Wrong value of \"finished\", ignored" );
	    // return;
	}
	    
    }	
    
    /**
     * Removes a completed instance of SingleParser from the SingleParser list.
     * 
     * @param srcID Corresponding source ID of the completed SingleParser.
     */
    synchronized void killSingleParser ( long srcID ) {
	parserList.remove ( new Long ( srcID ) );
    }
    
    IOracle getOracle () {
	return this.oracle;
    }
    
}





