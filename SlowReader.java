import java.io.*;
import java.util.*;

class SlowReader implements Runnable {

  FileInputStream fis = null;
  PipedOutputStream pos;
  byte [] buffer;

  SlowReader(PipedOutputStream pos, String fname) 
  	throws IOException {
    try {
      fis = new FileInputStream(fname);
    } catch (IOException ioe) {
      System.out.println("Error in SlowReader/Run():" + ioe);
      throw ioe;
    }
    this.pos = pos;
    buffer = new byte[100];
  }
  
  public void run() {

    int cnt = 0;
    boolean done = false;
    
    while (!done) {
      try {
	cnt = fis.read(buffer);
	if (cnt == -1) {
	  done = true;
	  pos.close();
	  break;
	}
	pos.write(buffer, 0, cnt);
	Thread.currentThread().sleep(1000);
	System.out.print("z");
      } catch (IOException ioe) {
	System.out.println("Error in SlowReader/Run():" + ioe);
      } catch (InterruptedException ie) {
      }
    }
  }

}
