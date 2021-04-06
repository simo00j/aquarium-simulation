package aquarium;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import java.io.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Aquarium {
    private final ArrayList<Fish> fish = new ArrayList<Fish>();
    private final ArrayList<Viewer> viewers = new ArrayList<Viewer>();
    private final String name = "Aquarium";
    private String backgroundColor = "black";
    int width;
    int height;

    public void addViewer(Viewer v){
        this.viewers.add(v);
    }

    public void addFish(Fish f){
        fish.add(f);
    }

    public void delFish(String fishName){
        this.fish.removeIf(f -> f.getName().equals(fishName));
    }

    public void delViewer(String viewerName){
        viewers.removeIf(v -> v.getName().equals(viewerName));
    }

    public void create() throws IOException{
        parseFile("resources/data/aquarium.txt");
        for (Viewer v : viewers) {
            Pane pane = test();
            Scene scene = new Scene(pane, v.viewer_width, v.viewer_height);
            pane.setStyle("-fx-background-color: linear-gradient(to left, #1fdedb, #1f7c91);");

            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle(v.getName());
            stage.setResizable(false);
            stage.show();

            break; // TO BE REMOVED !!!!!!!!!!!

        }
    }

    public void moveFish(){
        for (Fish f : fish){
            f.move();
        }
    }

    Pane test(){
        Pane pane = new Pane();
        Fish f;
        Random r = new Random();
        for (int i = 0; i < 40; i++) {
            int w = r.nextInt(viewers.get(0).getWidth())/10;
            if (w>100){
                w /=10;
            }
            f = new Fish(r.nextInt(viewers.get(0).getWidth()), r.nextInt(viewers.get(0).getWidth()), w, w);
            fish.add(f);
            pane.getChildren().add(f.getImageView());
        }
        pane.setStyle(String.format("-fx-background-color: %s;", this.backgroundColor));
        return pane;
    }

    void parseFile(String filename) throws IOException {
        try {
            FileInputStream fs = new FileInputStream(filename);
            DataInputStream in = new DataInputStream(fs);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));

            Scanner scanner = new Scanner(br);
            String line = scanner.nextLine();
            this.width = Integer.parseInt(line.split("x")[0]);
            this.height = Integer.parseInt(line.split("x")[1]);
            Viewer v;

            while (scanner.hasNextLine()) {
                line = scanner.nextLine();
                String name = new String(line.split(" ")[0]);
                int viewer_x = Integer.parseInt(line.split(" ")[1].split("\\+")[0].split("x")[0]);
                int viewer_y = Integer.parseInt(line.split(" ")[1].split("\\+")[0].split("x")[1]);
                int viewer_width = Integer.parseInt(line.split(" ")[1].split("\\+")[1]);
                int viewer_height = Integer.parseInt(line.split(" ")[1].split("\\+")[2]);
                v = new Viewer(name, viewer_x, viewer_y, viewer_width, viewer_height);
                this.addViewer(v);
            }
        }
        catch (IOException e){
            System.out.println("Error, couldn't open file");
        }
    }

}
