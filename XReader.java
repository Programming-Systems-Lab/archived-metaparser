import java.io.*;
import org.xml.sax.*;
import oracle.xml.parser.schema.*;

class XReader {

  BufferedReader br = null;
  PipedOutputStream pos = null;
  int curLine = 0;
  int curCol = 0;
  String buf = null;
  SubParser sp = null;
  String instance = null;

  // used for SubParsers: have we reached the "outermost" tag yet?
  int depth;
  String element;

  public void setDepth(int d) {depth = d;}
  public int getDepth() {return depth;}
  public void setElement(String e) {element = e;}
  public String getElement() {return element;}

  XReader(Reader r, PipedOutputStream o, XMLSchema s, String inst) 
    throws IOException {
    try {
      br = new BufferedReader(r);
      sp = new SubParser(o, s, inst);
    } catch (IOException ioe) {
      System.out.println(instance + "Error in XReader constructor 1");
      throw ioe;
    }

    instance = inst;
    pos = o;
    curLine = 0;
    curCol = 1;

    Thread t = new Thread(sp);
    t.start();
  }

  XReader(Reader r, PipedOutputStream o, XMLSchema s, String inst, Locator l) 
    throws IOException {
    try {
      br = new BufferedReader(r);
      sp = new SubParser(o, s, inst);
    } catch (IOException ioe) {
      System.out.println(instance + "Error in XReader constructor 2.1");
      throw ioe;
    }

    instance = inst;
    pos = o;
    curLine = 0;

    skip(l);

    System.out.println(instance + "XReader buffer:" + buf);
    System.out.println(instance + "XReader(" + curCol + "):" 
    	+ buf.substring(curCol-1));

    Thread t = new Thread(sp);
    t.start();
  }

  void skip(Locator l) throws IOException {
    int tgtLine = l.getLineNumber();
    try {
      while (curLine < tgtLine) {
        buf = br.readLine();
	curLine++;
      }
    } catch (IOException ioe) {
      System.out.println(instance + "Error in XReader constructor 2.2");
      throw ioe;
    }

    curCol = l.getColumnNumber();
  }


  void send(String s) throws IOException {
    try {
      System.err.println(instance + "sending:" + s);
      pos.write(s.getBytes());
    } catch (IOException ioe) {
      System.out.println(instance + "Error in send");
      throw ioe;
    }
  }
    
  void flush(Locator l) throws IOException {
    int tgtLine = l.getLineNumber();
    int tgtCol = l.getColumnNumber();
    // System.err.println(instance + "req to flush " + tgtLine +":"+tgtCol);
    // System.err.println(instance + "cur= " + curLine +":"+curCol);

    try {
      if (tgtLine > curLine) {
        if (buf != null) {
	  String s = buf.substring(curCol-1);
	  System.err.println(instance + "flushing:" + s);
	  pos.write(s.getBytes());
	}
	curCol = 1;
	while (tgtLine > curLine+1) {
	  buf = br.readLine();
	  System.err.println(instance + "flushing:" + buf);
	  pos.write(buf.getBytes());
	  curLine++;
	}
	buf = br.readLine();
	curLine++;
      }
      // System.err.println(instance + "cur= " + curLine +":"+curCol);
      // System.err.println(instance + "buf=" + buf);
      if (buf != null) {
        String s =buf.substring(curCol-1, tgtCol-1);
	System.err.println(instance + "flushing:" + s);
	pos.write(s.getBytes());
      }
      curCol = tgtCol;
    } catch (IOException ioe) {
      System.out.println(instance + "Error in flush");
      throw ioe;
    }
  }

  void close(boolean flush) throws IOException {
    try {
      if (flush) {
	String s = buf.substring(curCol-1);
	System.err.println(instance + "flushing:" + s);
	pos.write(s.getBytes());
      }
      br.close();
      pos.close();
    } catch (IOException ioe) {
      System.out.println(instance + "Error in close");
      throw ioe;
    }
  }

}
