import java.net.*;
import java.io.*;

public class zServer implements Runnable {
  private static final int portNumber = 12345;
  private static final String GESTURE_END = "END";
  private static final String SWITCH_SCREEN = "SWITCH";

  private Parser parser = null;
  private BufferedReader in = null;
  private ServerSocket serverSocket = null;
  private Socket clientSocket = null;

  private Point pt;
  private Point lastPt;

  public boolean isSparkle, isAnimal, isNewPoint;
  public boolean switchUserState;

  public zServer() {
    parser = new Parser();
    this.pointAck();
  }

  public void Connect() {

    //Listen
    try {
      serverSocket = new ServerSocket(portNumber);
    } 
    catch (IOException e) {
      System.out.println("Server: Could not listen on port "+ portNumber);
      System.out.println(e.getMessage());
      System.exit(-1);
    }

    System.out.println("Server: Waiting for connection on port "+ portNumber);

    //Accept connection
    try {
      clientSocket = serverSocket.accept();
    } 
    catch (IOException e) {
      System.out.println("Accept failed: "+ portNumber);
      System.exit(-1);
    }

    //Create stream
    try {
      in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    } 
    catch (IOException e) {
      System.out.println("Server: Read failed");
      System.exit(-1);
    }

    System.out.println("Server: Client connected on port: " + portNumber);
  }

  public void run() {
    while (true) {
      try {
        String input;
        if ((input = in.readLine()) != null) {

          System.out.print(input);
          System.out.print(",");

          // If END, call animal() with last point
          if (input.equals(GESTURE_END)) {
            pt = new Point(lastPt);
            isAnimal = true;
            isNewPoint = true;
          } 
          else if (input.equals(SWITCH_SCREEN)) {
            switchUserState = true;
          } 
          else if ((pt = parser.parsePoint(input)) != null) {
            //                    System.out.print(pt.toString());
            lastPt = new Point(pt);
            isSparkle = true;
            isNewPoint = true;
          }
        }
        Thread.sleep(10L);
      } 
      catch (Exception e) {
        System.out.println("Server:run()");
        System.out.println(e.getMessage());
      }
    }
  }

  public void pointAck() {
    this.isNewPoint = false;
    this.isSparkle = false;
    this.isAnimal = false;
  }

  public Point getNewPoint() {
    return new Point(this.pt);
  }

  public void Close() {
    System.out.println("Server: Closing Connection");
    try {
      in.close();
      serverSocket.close();
      clientSocket.close();
    } 
    catch (IOException e) {
      System.out.println("Exception caught when trying to close server ");
      System.out.println(e.getMessage());
    }
  }
}
