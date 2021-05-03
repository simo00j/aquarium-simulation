package aquarium.gui;

import aquarium.Config;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

import java.util.ArrayList;

public class Viewer {
    public Stage stage;
    public BorderPane pane;
    public ArrayList<Fish> fish = new ArrayList<>();

    public Viewer(int viewer_x, int viewer_y, int viewer_width, int viewer_height){
        this.stage = new Stage();
        this.stage.setX(viewer_x);
        this.stage.setY(viewer_y);
        this.stage.setHeight(viewer_height);
        this.stage.setWidth(viewer_width);
        this.stage.setTitle(Config.properties.getProperty("id"));
        this.stage.setResizable(false);
        this.pane = new BorderPane();
        this.pane.setStyle("-fx-background-color: linear-gradient(to bottom, #1fdedb, #1f7c91);");
        Scene scene = new Scene(this.pane, stage.getWidth(), stage.getHeight());
        this.stage.setScene(scene);
    }

    public void addFish(Fish fish) {
        this.fish.add(fish);
        this.pane.getChildren().add(fish.getImageView());
    }
    public void moveFish(){
            for (Fish f : this.fish){
                f.move();
            }
    }
}
