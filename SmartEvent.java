package psl.metaparser;

/**
 * A representation of a smart event that will come from local GC to the 
 * metaparser. Changes will be made to this class after further discussion.
 *
 * @author Jing Fan
 * @version 0.9
 */
public class SmartEvent {
    private long srcID;
    private boolean isFinished;
    private String content;
    
    public SmartEvent () {
	srcID = -1l;
	isFinished = false;
	content = "";
    }
    
    public long getSrcID () { return this.srcID; }
    
    void setSrcID ( long srcID ) {
	this.srcID = srcID;
    }
    
    public boolean getIsFinished () { return this.isFinished; }
    
    void setIsFinished ( boolean isFinished ) {
	this.isFinished = isFinished;
    }

    public String getContent () { return this.content; }
    
    void setContent ( String content ) {
	this.content = content;
    }
    
    public String toString () {
	String result = "<smartevent";
	if ( srcID >= 0 )
	    result += ( " srcID=\"" + srcID + "\"" );
	if ( isFinished )
	    result += ( " finished=\"true\"" );
	if ( content.length () > 0 ) {
	    result += ( "><![CDATA[" + content + "]]>" );
	    result += "</smartevent>";
	} else {
	    result += "/>";
	}
	return result;
    }
}
