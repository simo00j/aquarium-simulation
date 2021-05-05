package aquarium;

import aquarium.client.Client;
import aquarium.client.Ping;
import aquarium.gui.Fish;
import aquarium.gui.Prompt;
import aquarium.gui.Viewer;
import aquarium.parse.ParseServerIncoming;
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
    public Prompt prompt;
    public LinkedList<String> commandsList;
    //public static final Logger logger = Logger.getLogger(Connection.class.getName());

    public Connection(Stage primaryStage) {
        this.commandsList = new LinkedList<>();
        this.client = new Client();
        this.stdIn = new BufferedReader(new InputStreamReader(System.in));

        initializeConnection();

        this.prompt = new Prompt(this);
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

        Thread promptThread = new Thread(new Prompt(this));
        promptThread.setDaemon(true);
        promptThread.start();

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

    public void startFish(String name){
        for (Fish f : fishList){
            if (f.getName().equals(name)) {
                f.move();
                break;
            }
        }
    }

    public void startFish(Fish fish){
        fish.move();
    }

    public void startFish(){
        for (Fish f : fishList){
            f.move();
        }
    }

    public void delFish(String name){
        for (Fish f : fishList){
            if (f.getName().equals(name)) {
                fishList.remove(f);
                break;
            }
        }
    }

    public void endConnection() {
        try {
            this.client.getSocket().close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void initializeConnection() {
        if (Config.properties.getProperty("id") != null) {
            this.client.out.println("hello in as " + Config.properties.getProperty("id"));
        } else {
            this.client.out.println("hello");
        }
        commandsList.add("hello");
        this.client.out.println("getFishes");
        commandsList.add("getFishes");

    }
}
