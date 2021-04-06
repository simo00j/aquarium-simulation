package aquarium;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    private Color backgroundColor;

    @Override
    public void start(Stage primaryStage) throws IOException {
        Aquarium aquarium = new Aquarium();
        aquarium.create();

        //////////////************************** Menu Buttons **************************//////////////

        ToolBar toolbar = new ToolBar();

        /* Aquarium menu */
        MenuButton aquariumButton = new MenuButton("Aquarium");

        MenuItem moveFishButton = new MenuItem("Let fish start swimming !");
        moveFishButton.setOnAction(event -> aquarium.moveFish());
        aquariumButton.getItems().add(moveFishButton);


        /* View menu */
        MenuButton viewButton = new MenuButton("View");

        /* Help menu */
        MenuButton helpButton = new MenuButton("Help");


        BorderPane pane = new BorderPane();
        toolbar.getItems().add(aquariumButton);
        toolbar.getItems().add(viewButton);
        toolbar.getItems().add(helpButton);
        HBox statusBar = new HBox();
        Pane appContent = new Pane();
        pane.setTop(toolbar);
        pane.setCenter(appContent);
        pane.setBottom(statusBar);
        Scene scene = new Scene(pane, 300, 300);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Aquarium App");
        primaryStage.setResizable(true);
        MenuItem darkModeItem = new MenuItem("Enable/Disable dark mode");


        darkModeItem.setOnAction(e -> {
            if (backgroundColor == Color.BLACK){
                pane.setStyle("-fx-background-color : white");
                backgroundColor = Color.WHITE;
            } else{
                pane.setStyle("-fx-background-color : black;");
                backgroundColor = Color.BLACK;
            }
        });
        darkModeItem.setAccelerator(new KeyCodeCombination(KeyCode.T, KeyCombination.CONTROL_DOWN));
        Menu ViewMenu = new Menu("View");
        ViewMenu.getItems().add(darkModeItem);
        MenuBar menuBar = new MenuBar();
        menuBar.setUseSystemMenuBar(true);
        menuBar.getMenus().add(ViewMenu);
        VBox vBox = new VBox(menuBar);
        pane.getChildren().add(vBox);
        primaryStage.show();

    }
    public static void main(String[] args) {
        launch(args);
    }
}
