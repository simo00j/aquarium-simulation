package aquarium.client;

import aquarium.Config;

import java.io.*;
import java.net.*;

public class Client {
    private Socket socket = null;
    public PrintWriter out = null;
    public BufferedReader in = null;

    public Client() {
        try {
            this.socket = new Socket(InetAddress.getByName( Config.properties.getProperty("controller-address")), Integer.parseInt(Config.properties.getProperty("controller-port")));
            System.out.println("Connected to server "+ InetAddress.getByName( Config.properties.getProperty("controller-address")) + " on port " + Integer.parseInt(Config.properties.getProperty("controller-port")));
            this.out = new PrintWriter(this.socket.getOutputStream(), true);
            this.in = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        }catch (IOException e){
            System.out.println("The server is not running or can't be reachable");
            System.exit(0);
        }
    }

    public Socket getSocket() {return socket;}
}