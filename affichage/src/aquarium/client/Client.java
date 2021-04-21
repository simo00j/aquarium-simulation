package aquarium.client;
import aquarium.gui.Fish;
import javafx.scene.layout.Pane;

import java.io.*;
import java.net.*;
import java.util.Random;

public class Client {
    private Socket socket = null;
    public PrintWriter out = null;
    public BufferedReader in = null;

    public Client(String ip, int port) {
        try {
            this.socket = new Socket(InetAddress.getByName(ip), port);
            System.out.println("Connected to server "+ InetAddress.getByName(ip) + " on port " + port);
            this.out = new PrintWriter(this.socket.getOutputStream(), true);
            this.in = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        }catch (IOException e){
            System.out.println("The server is not running or can't be reachable");
            System.exit(0);
        }
    }

    public Socket getSocket() {return socket;}
}