package aquarium;

import aquarium.client.Client;
import aquarium.gui.Fish;
import aquarium.gui.Viewer;
import aquarium.parse.ParseServerIncoming;
import aquarium.parse.ParseUserInput;
import aquarium.parse.Parser;
import javafx.application.Platform;
import javafx.stage.Stage;

import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.stream.Collectors;

public class Connection {
    public Viewer viewer;
    public Client client;
    public ArrayList<Fish> fishList = new ArrayList<>();
    public BufferedReader stdIn;
    //public static final Logger logger = Logger.getLogger(Connection.class.getName());

    public Connection(Stage primaryStage) {
        this.client = new Client();
        this.stdIn = new BufferedReader(new InputStreamReader(System.in));
        primaryStage.setOnCloseRequest(e -> {
            endConnection();
            Platform.exit();
            System.exit(0);
        });
        this.viewer = new Viewer(primaryStage, 0, 0, 1280, 720);
    }

    public void launch() {
        Thread thread = new Thread(() -> {
            Platform.runLater(() -> this.viewer.stage.show());
            Platform.runLater(() -> {
                this.addFish(new Fish("Spongebob", 100, 120, new Point(400, 400),  new Point(600, 600), 0));
                this.startFish();
                Parser p = new Parser();
                String scanned = "list [PoissonRouge at 92x40,60x45,5] [PoissonClown at 200x300,90x80,5]";
                LinkedList<Fish> fishList = p.parseFishList(scanned);
                System.out.println(fishList.size());
                fishList.forEach(f -> this.addFish(f));
                fishList.forEach(f -> f.move());
            });

            while(this.client.getSocket().isConnected()){
                //Thread.sleep(Config.properties.getProperty("display-timeout-value"));
                //this.client.out.println("ls");
                //this.client.out.flush();
            }
        });
        thread.setDaemon(true);
        thread.start();
        Thread pingThread = new Thread(new Ping(this.client.out));
        pingThread.setDaemon(true);
        pingThread.start();
        Thread userInputThread = new Thread(new ParseUserInput(this.stdIn, this.client.out));
        userInputThread.setDaemon(true);
        userInputThread.start();
        Thread ServerIncomingThread = new Thread(new ParseServerIncoming(this));
        ServerIncomingThread.setDaemon(true);
        ServerIncomingThread.start();
    }

    public void addFish(Fish fish) {
        if (!fishList.stream().map(f -> f.getName()).collect(Collectors.toList()).contains(fish.getName())) {
            this.fishList.add(fish);
            this.viewer.pane.getChildren().add(fish.getImageView());
        }
    }

    /* this function is probably not necessary*/
    public void delFish(String name) {
        this.fishList.removeIf(f -> f.getName().equals(name));
        // Still needs to be removed from the viewer
    }

    public void startFish(){
        for (Fish f : this.fishList){
            f.move();
        }
    }

    public void endConnection() {
        try {
            this.client.in.close();
            this.client.out.close();
            this.client.getSocket().close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
