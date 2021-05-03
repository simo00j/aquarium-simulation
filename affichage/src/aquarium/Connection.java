package aquarium;

import aquarium.client.Client;
import aquarium.gui.Fish;
import aquarium.gui.Viewer;
import javafx.application.Platform;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Connection {
    public Viewer viewer;
    public Client client;
    BufferedReader stdIn;

    public Connection() {
        this.client = new Client();
        this.stdIn = new BufferedReader(new InputStreamReader(System.in));
        this.viewer = new Viewer(100, 100, 720, 480);
    }

    public void launch() {
        Thread thread = new Thread(() -> {
            Platform.runLater(() -> this.viewer.stage.show());
            String userInput;
            System.out.print("> ");
            Platform.runLater(() -> {
                this.viewer.addFish(new Fish("PoissonRouge", 400, 400, 70, 50));
                this.viewer.moveFish();
            });
            try {
                while ((userInput = stdIn.readLine()) != null) {
                    client.out.println(userInput);
                    System.out.println("< " + this.client.in.readLine());
                    System.out.print("> ");
                }
                endConnection();
                this.stdIn.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        thread.setDaemon(true);
        thread.start();
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
