package aquarium;

import javafx.animation.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.shape.CubicCurveTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

import java.util.Random;

public class Fish {
    private ImageView iv;
    private PathTransition pathTransition;
    String name;

    Fish(int x, int y, int fish_width, int fish_height){
        iv = new ImageView();
        iv.setImage(new Image("file:resources/images/clown-fish.png"));

        iv.setFitWidth(fish_width);
        iv.setFitHeight(fish_height);
        iv.setX(x);
        iv.setY(y);

        Path path = new Path();
        Random r = new Random();
        path.getElements().add(new MoveTo(iv.getX(), iv.getY()));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600), r.nextInt(600)));
        path.getElements().add(new CubicCurveTo(600, 600, 600, 600, 600, 600));

        this.pathTransition = new PathTransition();
        pathTransition.setDuration(Duration.millis(30000));
        pathTransition.setPath(path);
        pathTransition.setNode(iv);
        pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
        //pathTransition.setCycleCount(Timeline.INDEFINITE);
        //pathTransition.setAutoReverse(true);
    }

    public ImageView getImageView() {
        return iv;
    }
    public PathTransition getPathTransition() {
        return this.pathTransition;
    }
    public String getName(){return name;}

    public void move(){
        this.pathTransition.play();
    }
}
