package psl.metaparser;

import org.xml.sax.Attributes;

import org.jdom.Element;

/**
 * This interface defines the methods that will be called when a tag is hit.
 *
 * @author Jing Fan
 * @version 0.9
 */

public interface IMetaparserModule {
    
    /** Returns the first tag associated with this module */
    public String getAssociatedTagName ();
    
    /** Returns all the tags associated with this module */
    public String[] getAllAssociatedTagNames ();
    
    /** Returns if this module is a singleton */
    public boolean isSingleton ();
    
    /** This is called when a tag associated with this module opens */
    public void tagOpening ( String namespaceURI, String localName,
			     String rawName, Attributes atts );

    /** This is called when a tag associated with this module closes */
    public void tagClosing ( String namespaceURI, String localName, 
			     String rawName, boolean isValid,
			     Element content );
    
    /** This is called when a non-singleton module finishes */
    public void destroy ();
}

