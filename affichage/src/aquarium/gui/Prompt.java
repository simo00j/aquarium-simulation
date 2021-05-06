package aquarium.gui;

import aquarium.Connection;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class Prompt implements Runnable {

    Stage stage;
    Connection connection;
    TextArea response;


    public Prompt(Connection connection) {
        this.connection = connection;
        this.stage = new Stage();
        stage.setTitle("Client prompt");

        VBox box = new VBox(5);
        
        TextField command = new TextField();
        command.setPromptText("Enter command here.");

        this.response = new TextArea();
        response.setPrefRowCount(10);
        response.setEditable(false);


        Button example = new Button("Run example of commands");
        example.setOnAction(actionEvent -> {
            //TODO: Add file for example of commands and actions to run it
        });
        box.getChildren().addAll(command, response, example);
        box.setAlignment(Pos.CENTER);

        response.setStyle("-fx-text-fill: blue; -fx-highlight-fill: null;");
        command.setStyle("-fx-text-fill: green;");

        command.setOnKeyPressed( event -> {
            if( event.getCode() == KeyCode.ENTER ) {
                sendCommand(command.getText());
                command.setText("");
            }
        });

        stage.setScene(new Scene(box, 400, 250));
    }

    public void sendCommand(String scanned) {
        this.connection.commandsList.add(scanned);
        this.connection.client.out.println(scanned);
        this.connection.client.out.flush();
    }

    public void addResponse(String str) {
        this.response.appendText(str);
    }

    @Override
    public void run() {
        Platform.runLater(() -> this.stage.show());
    }
}
