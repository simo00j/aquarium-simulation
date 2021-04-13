package aquarium;
import java.io.*;
import java.net.*;

public class Client {

  final int port;
  final InetAddress address;
  final Socket soc;
  final PrintWriter out;
  final BufferedReader in;

  public Client(String ip, int port)throws UnknownHostException, IOException {
      this.port = port; 
      this.address = InetAddress.getByName(ip);
      this.soc = new Socket(this.address,this.port);
      System.out.println("listen on port "+this.port);
      this.out=new PrintWriter(this.soc.getOutputStream(),true);
      this.in=new BufferedReader(new InputStreamReader(this.soc.getInputStream()));
  }

  public Client()throws UnknownHostException, IOException {
      this.port = 5555; 
      this.address = InetAddress.getLocalHost();
      this.soc = new Socket(this.address,this.port);
      System.out.println("listen on port "+this.port);
      this.out=new PrintWriter(this.soc.getOutputStream(),true);
      this.in=new BufferedReader(new InputStreamReader(this.soc.getInputStream()));
  }

  public Socket getSocket(){
    return this.soc;
  }

  public void CloseCon()throws UnknownHostException, IOException{
    this.in.close();
    this.out.close();
    this.soc.close();
  }
 
 public static void main(String[] args) throws UnknownHostException, IOException{

   Client c=new Client();
   String entree,sortie;

    BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
     while (true) {
       entree=c.in.readLine();
       if(entree!=null) 
          System.out.println("Serveur>"+entree);
       if(entree.equals("bye")) 
          break;
       sortie=stdin.readLine();
       if(sortie!=null) {
          System.out.println("Client>"+sortie);
          c.out.println(sortie);
       }
     }
     c.CloseCon();
 
 }
}