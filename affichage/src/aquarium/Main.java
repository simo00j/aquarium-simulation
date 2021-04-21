package aquarium;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        Controller controller = new Controller(primaryStage);
        controller.stage.show();
    }
    public static void main(String[] args) {
        launch(args);
    }
}
