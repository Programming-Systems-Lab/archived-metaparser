package psl.oracle.impl;

/**
 * A representation of a schema fragment that will fly between oracle and
 * metaparser. Changes will be made to this class after further discussion
 * with developer of oracle.
 *
 * @author Jing Fan
 * @version 0.9
 */
public class SchemaFragment {
    private long srcID;
    private String name;
    private String path;
    private String nameSpace;
    private String description;
    private String moduleName;
    private boolean isSingleton;
    private String instanceName;

    public SchemaFragment () {
	srcID = -1;
	name = null;
	path = null;
	nameSpace = null;
	description = null;
	moduleName = null;
	isSingleton = false;
	instanceName = null;
    }    
    
    public String toString () {
        return ( srcID + ": " + name + "\n" + path + "\n" + 
		 nameSpace + "\n" + description + "\n" + 
		 moduleName + "\n" + isSingleton + "\n" + instanceName );
    }
    
    public long getSrcID () {
	return this.srcID;
    }
    
    public void setSrcID ( long srcID ) {
	this.srcID = srcID;
    }
	
    public String getName () {
	return this.name;
    }
    public void setName ( String name ) {
	this.name = name;
    }
    
    public String getPath () {
	return this.path;
    }
    
    public void setPath ( String path ) {
	this.path = path;
    }

    public String getNameSapce () {
	return this.nameSpace;
    }
    
    public void setNameSpace ( String nameSpace ) {
	this.nameSpace = nameSpace;
    }
    
    public String getDescription () {
	return this.description;
    }

    public void setDescription ( String description ) {
	this.description = description;
    }

    public String getModuleName () {
	return this.moduleName;
    }

    public void setModuleName ( String module ) {
	this.moduleName = module;
    }

    public boolean getIsSingleton () {
	return this.isSingleton;
    }
    
    public void setIsSingleton ( boolean singleton ) {
	this.isSingleton = singleton;
    }

    public String getInstanceName () {
	return this.instanceName;
    }

    public void setInstanceName ( String instance ) {
	this.instanceName = instance;
    }
    
}


