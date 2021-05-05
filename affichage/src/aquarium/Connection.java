package aquarium;

import aquarium.client.Client;
import aquarium.client.Ping;
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
        this.client.out.println("hello");
        primaryStage.setOnCloseRequest(e -> {
            endConnection();
            Platform.exit();
            System.exit(0);
        });
        this.viewer = new Viewer(primaryStage, 1280, 720);
    }

    public void launch() {
        Thread thread = new Thread(() -> Platform.runLater(() -> {
            this.viewer.stage.show();
            this.addFish(new Fish("Spongebob", 100, 120, new Point(400, 400),  new Point(600, 600), 5));
            this.startFish();
            String s2 = "addFish PoissonRouge at 92x40,60x45, RandomWayPoint";
            Parser.parseAddFish(s2, this);
            this.fishList.forEach(this::addFish);
            this.fishList.forEach(Fish::move);
        }));
        thread.setDaemon(true);
        thread.start();

        Thread pingThread = new Thread(new Ping(this.client.out));
        pingThread.setDaemon(true);
        pingThread.start();

        Thread userInputThread = new Thread(new ParseUserInput(this.stdIn, this));
        userInputThread.setDaemon(true);
        userInputThread.start();

        Thread ServerIncomingThread = new Thread(new ParseServerIncoming(this));
        ServerIncomingThread.setDaemon(true);
        ServerIncomingThread.start();
    }

    public void updateFish(Fish fish) {
        Fish oldFish = fishList.stream().filter(f -> f.getName().equals(fish.getName())).collect(Collectors.toList()).get(0);
        oldFish.updateFish(fish);
        Platform.runLater(oldFish::move);
    }
    public void addFish(Fish fish) {
        if (!fishList.stream().map(Fish::getName).collect(Collectors.toList()).contains(fish.getName())) {
            fishList.add(fish);
            Platform.runLater(() -> this.viewer.pane.getChildren().add(fish.getImageView()));
        }
    }

    public void startFish(){
        for (Fish f : fishList){
            f.move();
        }
    }

    public void startFish(Fish fish){
        fish.move();
    }

    public void endConnection() {
        try {
            this.client.getSocket().close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
