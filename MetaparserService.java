package psl.metaparser;

import psl.oracle.impl.SchemaFragment;
import psl.groupspace.*;
import psl.groupspace.impl.*;
import psl.metaparser.Metaparser;
import java.util.*;
import java.beans.*;

/**
 * An implementation of GroupspaceService interface, which sends query and
 * receives Oracle reply and smart event for metaparser
 *
 * @author Jing Fan
 * @version 0.9
 */
public class MetaparserService implements GroupspaceService,
					  GroupspaceCallback,
					  MetaparserServiceRole {
    // Class name of this service.
    private static final String className 
	= "psl.metaparser.MetaparserService";
    
    // Role name of this service.
    private static String roleName 
	= "psl.metaparser.MetaparserServiceRole";

    // Name(s) of event(s) this service will send out.
    private static final int METAPARSER_EVENT = 0;
    private static String[] thisEventName 
	= { "MetaparserEvent" };
    
    // Name(s) of event(s) this service will subscribe to.
    private static int SUBSCRIBE_ORACLE_EVENT = 0;
    private static int SUBSCRIBE_SMARTEVENT = 1;
    private static String[] subscribeEventName 
	= { "OracleEvent",
	    "SmartEvent" };
    
    // A reference to the parser that uses this service.
    private Metaparser parser;

    // Local reference to a Groupspace Controller
    private GroupspaceController gc;
    
    /** Default constructor. */
    protected MetaparserService () {
	this.parser = null;
    }
    
    /** Constructor with the reference of the calling metaparser */
    public MetaparserService ( Metaparser parser ) {
	this.parser = parser;
    }
    
    /** 
     * Defined within GroupspaceService interface to initialize 
     * this service.
     */
    public boolean gsInit ( GroupspaceController gc ) {
	this.gc = gc;
	gc.registerRole ( this.roleName, this );
	for ( int index = 0; index < subscribeEventName.length; index ++ ) 
	    gc.subscribeEvent( this, subscribeEventName[index] );
	
	return true;
    }
    
    /**
     * Defined within GroupspaceService interface to stop
     * this service.
     */
    public void gsUnload () {
	gc.unsubscribeAllEvents ( this );
	gc = null;
    }
    

    /**
     * Defined within GroupspaceService interface to start
     * this service.
     */
    public void run () {
	System.err.println ( "Starting Metaparser Service" );
    }
    

    /**
     * Defined within GroupspaceCallback interface to perform callbacks.
     *
     * @param ge The Groupspace Event that triggues this callback.
     */    
    public int callback ( GroupspaceEvent ge ) {
	String eventType = ge.getEventDescription ();
	if ( eventType.equals ( subscribeEventName[SUBSCRIBE_ORACLE_EVENT] ) )
	    processOracleReply ( ge );
	else if ( eventType.equals
		  ( subscribeEventName[SUBSCRIBE_SMARTEVENT] ) )
	    processSmartEvent  ( ge );
	else
	    System.err.println ( "Unknown event received" );
	return GroupspaceCallback.CONTINUE;
    }
    
    /** Accessor to the role name of this service */
    public String roleName () {
	return this.roleName;
    }
    
    /** 
     * This method is called to process reply from oracle.
     *
     * @param ge Oracle reply wrapped in a groupspace event
     */
    public synchronized void processOracleReply ( GroupspaceEvent ge ) {
	//	System.err.println
	//	    ( "Process reply from Oracle - Schema Fragment" );

	Object input = ge.getDbo ();
	if ( input instanceof SchemaFragment ) {
	    if ( parser != null ) 
		parser.processOracleReply ( ( SchemaFragment )input ) ;
	    else
		System.err.println ( "Empty Parser, skip reply" );
	} else {
	    System.err.println 
		( "Get an event that should not come from Oracle" );
	}
	return;
    }
    
    /**
     * This method is called to process smart event coming through GC.
     *
     * @param ge Smart event wrapped in a groupspace event
     */
    public synchronized void processSmartEvent ( GroupspaceEvent ge ) {
	
	Object input = ge.getDbo ();
	if ( input instanceof SmartEvent ) {
            if ( parser != null )
                parser.processSmartEvent ( ( SmartEvent )input );
            else 
                System.err.println ( "Empty Parser, skip event" );
        } else {
            System.err.println
                ( "Get an event that should not come from Oracle" );
        }
        return;
    }
    
    /**
     * This method is called to send a new query through the GC to 
     * Oracle. The content of the new query will be wrapped into a 
     * groupspace event.
     *
     * @param newOracleQuery Content of the new query.
     */
    public synchronized void setNewOracleQuery ( String newOracleQuery ) {
	synchronized ( newOracleQuery ) {
	    try {
		GroupspaceEvent ge =
		    new GroupspaceEvent	( new String ( newOracleQuery ),
					  thisEventName[METAPARSER_EVENT],
					  null, 
					  new String ( newOracleQuery ), 
					  true );
		System.err.println ( "Send event: " + newOracleQuery );
		gc.groupspaceEvent ( ge );
	    } catch ( PropertyVetoException pve ) {
		System.err.println ( "New Query Vetoed." );
	    } catch ( java.lang.NullPointerException npe ) {
		System.err.println ( "Here" );
		npe.printStackTrace ();
	    }
	}
    }
    
}









