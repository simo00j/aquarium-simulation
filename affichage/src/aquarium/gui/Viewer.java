package aquarium.gui;

import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Random;

public class Viewer {
    public Stage stage;
    public Pane pane;

    public Viewer(String name, int viewer_x, int viewer_y, int viewer_width, int viewer_height){
        this.stage = new Stage();
        this.stage.setX(viewer_x);
        this.stage.setY(viewer_y);
        this.stage.setHeight(viewer_height);
        this.stage.setWidth(viewer_width);
        this.stage.setTitle(name);
        this.stage.setResizable(false);
        this.pane = new Pane();
        this.pane.setStyle("-fx-background-color: linear-gradient(to bottom, #1fdedb, #1f7c91);");
        Scene scene = new Scene(this.pane, stage.getWidth(), stage.getHeight());
        this.stage.setScene(scene);
    }

    Pane testPane(){
        Pane pane = new Pane();
        Fish f;
        Random r = new Random();
        for (int i = 0; i < 40; i++) {
            int w = r.nextInt((int)this.stage.getWidth())/10;
            if (w > 100){
                w /= 100;
            }
            f = new Fish("PoissonRouge", r.nextInt((int)this.stage.getWidth()), r.nextInt((int)this.stage.getWidth()), w, w);
            pane.getChildren().add(f.getImageView());
        }
        pane.setStyle("-fx-background-color: linear-gradient(to left, #1fdedb, #1f7c91);");
        return pane;
    }

    public void addFish(Fish fish) {
        this.pane.getChildren().add(fish.getImageView());
    }
}
