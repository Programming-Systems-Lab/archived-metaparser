package psl.metaparser;

import java.util.Vector;

import org.jdom.Element;

/**
 * This class is used purely by SingleParser class to store properties of 
 * each tag it encounters. It's not supposed to be used outside the package.
 *
 * @author Jing Fan
 * @version 0.9
 */
class MetaparserTag {

    private Element content;
    private int start;
    private Vector data;

    MetaparserTag ( Element content, int start ) {
	this.content = content;
	this.start = start;
	data = new Vector ();
    }
    
    Element getContent () { return this.content; }
    
    String getTagName () { return content.getQualifiedName (); }
    
    int getStartIndex () { return this.start; }
    
    Vector getData () { return this.data; }

    void removeData () { data = new Vector (); }
    
    boolean isEmpty () { return ( 0 == data.size () ); }

    void addData ( int start, int length ) {
	data.add ( new MetaparserTag.Data ( start, length ) );
    }
    
    static class Data {
	
	int start;
	int length;
	
	Data ( int start, int length ) {
	    this.start = start;
	    this.length = length;
	}
	
	int getStartIndex () { return this.start; }
	
	int getLength () { return this.length; }
    }
}
	    
