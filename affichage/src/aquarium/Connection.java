package aquarium;

import aquarium.client.Client;
import aquarium.gui.Fish;
import aquarium.gui.Viewer;
import javafx.application.Platform;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

public class Connection {
    public Viewer viewer;
    public Client client;
    final private String name;
    BufferedReader stdIn;

    public Connection(String name) {
        this.name = "test Connexion";
        this.client = new Client(Config.properties.getProperty("server.post"), Integer.parseInt(Config.properties.getProperty("server.port")));
        this.stdIn = new BufferedReader(new InputStreamReader(System.in));
        this.viewer = new Viewer(name, 100, 100, 720, 480);
    }



    public void launch(){
        String userInput;
        System.out.print("> ");
        Platform.runLater(() -> this.viewer.addFish(new Fish("PoissonRouge", 40 , 50, 50, 50)));
        try {
            while ((userInput = stdIn.readLine()) != null)
            {
                client.out.println(userInput);
                System.out.println("< " + client.in.readLine());
                // PARSER ET TRAIRER LA REQUETE, MODIFIER L'AFFICHAGE SI BESOIN AVEC LA LIGNE SUIVANTE
                Platform.runLater(() -> this.viewer.addFish(new Fish("PoissonRouge", 80 , 100, 70, 50)));
                System.out.print("> ");
            }
            endConnection();
            stdIn.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public void endConnection() {
        try {
            this.client.in.close();
            this.client.out.close();
            this.client.getSocket().close();
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void sendMessage(String message) {
        this.client.out.println(message);
    }


    public String getName(){return name;}
}
