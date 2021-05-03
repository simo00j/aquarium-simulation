package aquarium;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        Connection connection = new Connection();
        connection.launch();
    }
    public static void main(String[] args) {
        launch(args);
    }
}
