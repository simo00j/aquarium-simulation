package aquarium;

import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class Controller {
    private Color backgroundColor;
    public Stage stage;
    public Aquarium aquarium;

    public Controller(Stage primaryStage){
        ToolBar toolbar = new ToolBar();
        /* Aquarium menu */
        MenuButton aquariumButton = new MenuButton("Aquarium");

        MenuItem loadAquarium = new MenuItem("Load aquarium example !");
        loadAquarium.setAccelerator(new KeyCodeCombination(KeyCode.L, KeyCombination.CONTROL_DOWN));
        loadAquarium.setOnAction(event -> {
            this.aquarium = new Aquarium("resources/data/aquarium2.txt");

        });

        MenuItem exitItem = new MenuItem("Exit Aquarium");
        exitItem.setAccelerator(new KeyCodeCombination(KeyCode.Q, KeyCombination.CONTROL_DOWN));
        exitItem.setOnAction(e -> {
            Alert quitAlert = new Alert(Alert.AlertType.CONFIRMATION, "Are you sure you want to quit ?", ButtonType.YES, ButtonType.CANCEL);
            quitAlert.showAndWait();
            if (quitAlert.getResult() == ButtonType.YES) {
                for (Connection connection : this.aquarium.connections) {
                    connection.endConnection();
                }
                System.exit(0);
            }
        });
        aquariumButton.getItems().addAll(exitItem, loadAquarium);


        /* View menu */
        MenuButton viewButton = new MenuButton("View");
        MenuItem darkModeItem = new MenuItem("Enable/Disable dark mode");
        darkModeItem.setAccelerator(new KeyCodeCombination(KeyCode.T, KeyCombination.CONTROL_DOWN));
        viewButton.getItems().add(darkModeItem);

        toolbar.getItems().addAll(aquariumButton, viewButton);

        BorderPane pane = new BorderPane();
        HBox statusBar = new HBox();
        Pane appContent = new Pane();
        pane.setTop(toolbar);
        pane.setCenter(appContent);
        pane.setBottom(statusBar);
        darkModeItem.setOnAction(e -> {
            if (backgroundColor == Color.BLACK){
                pane.setStyle("-fx-background-color : white");
                backgroundColor = Color.WHITE;
            } else{
                pane.setStyle("-fx-background-color : black;");
                backgroundColor = Color.BLACK;
            }
        });


        Scene scene = new Scene(pane, 480, 360);
        primaryStage.setScene(scene);
        primaryStage.setTitle(Config.properties.getProperty("app.name"));
        primaryStage.setResizable(true);

        MenuBar menuBar = new MenuBar();
        VBox vBox = new VBox(menuBar);
        pane.getChildren().add(vBox);
        primaryStage.getIcons().add(new Image("file:resources/images/clown-fish.png"));
        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent we) {
                System.exit(0);
            }
        });
        this.stage = primaryStage;
    }

}
