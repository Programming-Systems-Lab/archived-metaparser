package psl.metaparser;

import javax.swing.tree.DefaultMutableTreeNode;

/**
 * This class wraps the output parsed tree from metaparser with its source 
 * ID into a single object, which will be sent to the notifier service for
 * further manipulation.
 *
 * @author Jing Fan
 * @version 0.9
 */
public class MetaparserParsedTree {
    private DefaultMutableTreeNode root;
    private long srcID;
    
    public MetaparserParsedTree ( long srcID, DefaultMutableTreeNode root ) {
	this.root = root;
	this.srcID = srcID;
    }

    /**
     * This returns the tree by a reference to its root
     */
    public DefaultMutableTreeNode getTree () {
	return this.root;
    }
    
    /**
     * This returns the source ID of the tree
     */
    public long getSrcID () { return this.srcID; }
    
    public String toString () {
	return ( new String ( this.srcID + ": " + this.root.toString () ) );
    }
}
