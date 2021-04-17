package aquarium;
import aquarium.gui.Fish;
import aquarium.gui.Viewer;
import javafx.application.Platform;

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Aquarium {
    public final ArrayList<Fish> fish = new ArrayList<Fish>();
    public final ArrayList<Connection> connections = new ArrayList<Connection>();
    int width;
    int height;

    public Aquarium(String filename){
        parseFile(filename);
        for (Connection c : connections) {
            Thread thread = new Thread(() -> {
                Platform.runLater(() -> c.viewer.stage.show());
                c.launch();
            });
            thread.setDaemon(true);
            thread.start();
        }
    }

    void parseFile(String filename) {
        try {
            FileInputStream fs = new FileInputStream(filename);
            DataInputStream in = new DataInputStream(fs);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));

            Scanner scanner = new Scanner(br);
            String line = scanner.nextLine();
            this.width = Integer.parseInt(line.split("x")[0]);
            this.height = Integer.parseInt(line.split("x")[1]);

            while (scanner.hasNextLine()) {
                line = scanner.nextLine();
                String name = line.split(" ")[0];
                int viewer_x = Integer.parseInt(line.split(" ")[1].split("\\+")[0].split("x")[0]);
                int viewer_y = Integer.parseInt(line.split(" ")[1].split("\\+")[0].split("x")[1]);
                int viewer_width = Integer.parseInt(line.split(" ")[1].split("\\+")[1]);
                int viewer_height = Integer.parseInt(line.split(" ")[1].split("\\+")[2]);
                Connection c = new Connection(name);
                c.viewer = new Viewer(name, viewer_x, viewer_y, viewer_width, viewer_height);
                this.connections.add(c);
            }
        }
        catch (IOException e){
            System.out.println("Error, couldn't open file");
        }
    }

    public void addConnection(Connection c) { this.connections.add(c);}
    public void delConnection(String name){ this.connections.removeIf(connection -> connection.getName().equals(name));}
    public void addFish(Fish fish) { this.fish.add(fish);}

}
