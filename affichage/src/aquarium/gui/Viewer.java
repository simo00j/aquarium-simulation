package aquarium.gui;

import aquarium.Config;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Viewer {
    public Stage stage;
    public BorderPane pane;

    public Viewer(Stage primaryStage, int viewer_width, int viewer_height){
        this.stage = primaryStage;
        this.stage.setHeight(viewer_height);
        this.stage.setWidth(viewer_width);
        this.stage.setTitle(Config.properties.getProperty("id"));
        //this.stage.setResizable(false);
        this.pane = new BorderPane();
        //this.pane.setStyle("-fx-background-color: linear-gradient(to bottom, #1fdedb, #1f7c91);");
        this.pane.setStyle("-fx-background-image: url('file:resources/images/background.jpg'); -fx-background-repeat: no-repeat; -fx-background-size: cover, auto;");
        Scene scene = new Scene(this.pane, stage.getWidth(), stage.getHeight());
        this.stage.setScene(scene);

    }
}
