package psl.metaparser;

import java.io.*;
import org.xml.sax.*;
import oracle.xml.parser.schema.*;

/** Input controller.  Selectively feeds data to a SubParser.
  *
  * $Log$
  * Revision 2.2  2001-01-29 04:04:48  png3
  * Added package psl.metaparser statements.  Can you say "Oops?"
  *
  * Revision 2.1  2001/01/28 17:52:17  png3
  * New version of Metaparser: fully multithreaded.  PrintWriter logs.
  *
  */
class Validator {

  BufferedReader br = null;
  PipedWriter pos = null;
  int curLine = 0;
  int curCol = 0;
  String buf = null;
  SubParser sp = null;
  String inst = null;
  boolean debug;
  PrintWriter log = null;
  PrintWriter dbg = null;

  // used for SubParsers: have we reached the "outermost" tag yet?
  int depth;
  String element;

  synchronized void setDepth(int d) {depth = d;}
  synchronized int getDepth() {return depth;}
  synchronized void setElement(String e) {element = e;}
  synchronized String getElement() {return element;}

  synchronized void prLog(String m) {log.println(m);}
  synchronized void prDbg(String m) {if (debug) dbg.println(m);}

  Validator(String s, PipedWriter o, XMLSchema xmls, String inst, 
  	boolean debug) 
    throws IOException {

    final String fn = inst+"_ctor_1: ";
    
    try {
      br = new BufferedReader(new StringReader(s));
      sp = new SubParser(o, xmls, inst, this);
    } catch (IOException ioe) {
      System.err.println(fn + "I/O Exception:" + ioe);
      throw ioe;
    }

    this.debug = debug;
    try {
      String f1 = inst+".log";
      String f2 = inst+".dbg";
      log = new PrintWriter(new FileWriter(f1), true);
      log.println("Log started " + MPUtil.timestamp());
      if (debug) {
	dbg = new PrintWriter(new FileWriter(f2), true);
	dbg.println("Debug Log started " + MPUtil.timestamp());
      }
    } catch (IOException ioe) {
      System.err.println(fn + "unable to open log files");
      System.err.println(ioe);
      return;
    }

    this.inst = inst;
    pos = o;
    curLine = 0;
    curCol = 1;

    prDbg(fn+"Starting subParser");
    Thread t = new Thread(sp);
    t.start();
  }

  Validator(String s, PipedWriter o, XMLSchema xmls, String inst, 
  	boolean debug, Locator l) throws IOException {

    this(s, o, xmls, inst, debug);

    final String fn = inst+"_ctor_2: ";

    skip(l);

    prDbg(fn+"Validator buffer:" + buf);
    prDbg(fn+"Validator(" + curCol + "):" 
    	+ buf.substring(curCol-1));

  }

  void skip(Locator l) throws IOException {

    final String fn = inst+"_skip: ";

    prDbg(fn+"skip(" + MPUtil.printLoc(l) + ")");
    int tgtLine = l.getLineNumber();
    try {
      while (curLine < tgtLine) {
        buf = br.readLine();
	curLine++;
      }
    } catch (IOException ioe) {
      prLog(fn+"Error in skip:"+ioe);
      throw ioe;
    }
    curCol = l.getColumnNumber();
  }


  void send(String s) throws IOException {

    final String fn = inst+"_send: ";

    try {
      prDbg(fn+"sending:" + s);
      pos.write(s);
    } catch (IOException ioe) {
      prLog(fn+"Error in send:"+ioe);
      throw ioe;
    }
  }
    
  void flush(Locator l) throws IOException {

    final String fn = inst+"_flush: ";

    int tgtLine = l.getLineNumber();
    int tgtCol = l.getColumnNumber();
    // prDbg(fn+"req to flush " + tgtLine +":"+tgtCol);
    // prDbg(fn+"cur= " + curLine +":"+curCol);

    try {
      if (tgtLine > curLine) {
        if (buf != null) {
	  String s = buf.substring(curCol-1);
	  prDbg(fn+"flushing:" + s);
	  pos.write(s);
	}
	curCol = 1;
	while (tgtLine > curLine+1) {
	  buf = br.readLine();
	  prDbg(fn+"flushing:" + buf);
	  pos.write(buf);
	  curLine++;
	}
	buf = br.readLine();
	curLine++;
      }
      // prDbg(fn+"cur= " + curLine +":"+curCol);
      // prDbg(fn+"buf=" + buf);
      if (buf != null) {
        String s =buf.substring(curCol-1, tgtCol-1);
	prDbg(fn+"flushing:" + s);
	pos.write(s);
      }
      curCol = tgtCol;
    } catch (IOException ioe) {
      prLog(fn+"Error in flush:"+ioe);
      throw ioe;
    }
  }

  void close(boolean flush) throws IOException {

    final String fn = inst+"_close: ";

    prDbg(fn+"closing(" + flush + ")");
    try {
      if (flush) {
	String s = buf.substring(curCol-1);
	prDbg(fn+"flushing:" + s);
	pos.write(s);
      }
      br.close();
      pos.close();
    } catch (IOException ioe) {
      prLog(fn+"Error in close:"+ioe);
      throw ioe;
    }
  }

}
