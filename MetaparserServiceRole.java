package psl.metaparser;

import psl.groupspace.*;

/**
 * An interface that defines the role of MetaparserService.
 * 
 * @author Jing Fan
 * @version 0.9
 */
public interface MetaparserServiceRole {
    
    /** An method to process reply from oracle. */
    public void processOracleReply ( GroupspaceEvent ge );
    
    /** An method to process new smart event. */
    public void processSmartEvent ( GroupspaceEvent ge );
  
} 
