package aquarium;

import aquarium.client.Client;
import aquarium.client.Ping;
import aquarium.gui.Fish;
import aquarium.gui.Prompt;
import aquarium.gui.Viewer;
import aquarium.parse.ParseServerIncoming;
import javafx.application.Platform;
import javafx.stage.Stage;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Logger;
import java.util.stream.Collectors;

public class Connection {
    public Viewer viewer;
    public Client client;
    public ArrayList<Fish> fishList = new ArrayList<>();
    public BufferedReader stdIn;
    public Prompt prompt;
    public LinkedList<String> commandsList;
    public final Logger logger = Logger.getLogger(Connection.class.getName());

    public Connection(Stage primaryStage) {
        this.commandsList = new LinkedList<>();
        this.client = new Client();
        this.stdIn = new BufferedReader(new InputStreamReader(System.in));
        this.viewer = new Viewer(primaryStage);
        this.prompt = new Prompt(this);

        Thread ServerIncomingThread = new Thread(new ParseServerIncoming(this));
        ServerIncomingThread.setDaemon(true);
        ServerIncomingThread.start();

        primaryStage.setOnCloseRequest(e -> {
            this.endConnection();
            Platform.exit();
            System.exit(0);
        });
    }

    public void launch() {
        Thread pingThread = new Thread(new Ping(this.client.out));
        pingThread.setDaemon(true);
        pingThread.start();

        Platform.runLater(() -> {
            this.viewer.stage.setTitle(Config.properties.getProperty("id"));
            this.viewer.stage.show();
            this.prompt.stage.show();
        });
    }

    public void updateFish(Fish fish) {
        List<Fish> oldFishList = this.fishList.stream().filter(f -> f.getName().equals(fish.getName())).collect(Collectors.toList());
        Fish oldFish;
        if (oldFishList.size() > 0) {
            oldFish = oldFishList.get(0);
            oldFish.getPathTransition().stop();
            oldFish.updateFish(fish);
            this.startFish(oldFish);
        }
        else {
            this.addFish(fish);
            this.startFish(fish);
        }
    }

    public void addFish(Fish fish) {
        this.fishList.add(fish);
        Platform.runLater(() -> this.viewer.pane.getChildren().add(fish.getImageView()));
    }

    public void startFish(String name){
        for (Fish f : fishList){
            if (f.getName().equals(name)) {
                this.startFish(f);
                break;
            }
        }
    }

    public void startFish(Fish fish){
        Platform.runLater(fish::move);
    }

    public void delFish(String name){
        for (Fish f : fishList){
            if (f.getName().equals(name)) {
                this.fishList.remove(f);
                Platform.runLater(() -> this.viewer.pane.getChildren().remove(f.getImageView()));
                break;
            }
        }
    }

    public void sendCommand(String str) {
        this.client.out.println(str);
        this.client.out.flush();
        logger.info("> " + str);
    }

    public void endConnection() {
        this.sendCommand(("log out"));
        try {
            this.client.getSocket().close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void initializeConnection() {
        if (Config.properties.getProperty("id") != null) {
            sendCommand("hello in as " + Config.properties.getProperty("id"));
        } else {
            sendCommand("hello");
        }
    }
}
