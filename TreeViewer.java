package psl.metaparser;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JTree;
import javax.swing.JScrollPane;
import javax.swing.tree.TreeNode;

/**
 * A simple GUI to display the parsed tree from a SingleParser. It can do 
 * nothing meaningful, purely for debug purpose.
 */
class TreeViewer {
    
    TreeViewer ( TreeNode root ) {
	if ( root != null ) {
	    JFrame frame = new JFrame ( "Parsed Tree" );
	    frame.addWindowListener ( new WindowAdapter () {
		    public void windowClosing ( WindowEvent we) {
			System.exit( 0 );
		    }
		} );
	    frame.getContentPane ()
		.add ( new JScrollPane ( new JTree ( root ) ) );
	    frame.setSize ( 600, 600 );
	    frame.setVisible ( true );
	} else {
	}
    }
}
