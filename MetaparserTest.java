package psl.metaparser;

import java.io.FileReader;
import java.io.BufferedReader;

import psl.groupspace.*;
import psl.groupspace.impl.*;

import psl.util.*;

import java.beans.PropertyVetoException;

/**
 * A test class to see if Metaparser is working properly. It will read
 * from a file and send each line in three smart events with different
 * source IDs.
 * 
 * @author Jing Fan
 * @version 0.9
 */
public class MetaparserTest implements Runnable {
    
    // Three fake source IDs to simulate three different sources.
    private long parser1 = 100l;
    private long parser2 = 200l;
    private long parser3 = 300l;
    
    // Name of the file to read from.
    private String fileName;

    private GroupspaceController gc;
    
    public MetaparserTest ( String fileName, GroupspaceController gc ) {
	this.fileName = fileName;
	this.gc = gc;
    }
    
    public void run () {
	BufferedReader reader;
	try {
	    reader = new BufferedReader ( new FileReader ( fileName ) );
	} catch ( Exception e ) {
	    System.err.println ( "Cannot read from file: " + fileName );
	    return;
	}
	boolean loop = true;
	while ( loop ) { 
	    try {
		String current = reader.readLine ();
		SmartEvent p1 = new SmartEvent ();
		SmartEvent p2 = new SmartEvent ();
		SmartEvent p3 = new SmartEvent ();
		
		p1.setSrcID ( parser1 );
		p2.setSrcID ( parser2 );
		p3.setSrcID ( parser3 );
		
		if ( null == current ) {
		    p1.setIsFinished ( true );
		    p2.setIsFinished ( true );
		    p3.setIsFinished ( true );
		    loop = !loop;
		} else {
		    p1.setContent ( current + "\n" );
		    p2.setContent ( current + "\n" );
		    p3.setContent ( current + "\n" );
		}
		synchronized ( this ) {
		    GroupspaceEvent ge1 =
			new GroupspaceEvent ( p1, "SmartEvent", 
					      null, p1, true );
		    // System.err.println ( "Send event: " + p1 );
		    gc.groupspaceEvent ( ge1 );
		    GroupspaceEvent ge2 =
			new GroupspaceEvent ( p2, "SmartEvent", 
					      null, p2, true );
		    // System.err.println ( "Send event: " + p2 );
		    gc.groupspaceEvent ( ge2 );
                    GroupspaceEvent ge3 =
                        new GroupspaceEvent ( p3, "SmartEvent",
                                              null, p3, true );
		    // System.err.println ( "Send event: " + p3 );
                    gc.groupspaceEvent ( ge3 );
		} 
		Thread.yield ();
	    } catch ( java.io.IOException ioe ) {
		System.err.println ( "Can't read from file" );
		loop = !loop;
	    } catch ( PropertyVetoException pve ) {
		System.err.println ( "New Query Vetoed." );
		loop = !loop;
	    }
	}
    }
    
    public static void main ( String[] args ) {
	if ( args.length < 1 ) {
	    System.out.println ( "Usage: java psl.metaparser.MetaparserTest [XML URL]" );
	    System.exit ( 0 );
	}
	String uri = args[0];
	for ( int i = 1; i < args.length; i ++ )
	    uri += ( " " + args[i] );

	GroupspaceController gc = new GroupspaceController();
	Metaparser test = new Metaparser ( gc );
	MetaparserTest current = new MetaparserTest ( uri, gc );
	new Thread ( current ).start ();
    }
}




