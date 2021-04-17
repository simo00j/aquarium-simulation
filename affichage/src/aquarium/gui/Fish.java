package aquarium.gui;

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

    public Fish(String name, int x, int y, int fish_width, int fish_height){
        this.name = name;
        this.iv = new ImageView();
        this.iv.setImage(new Image("file:resources/images/clown-fish.png"));

        this.iv.setFitWidth(fish_width);
        this.iv.setFitHeight(fish_height);
        this.iv.setX(x);
        this.iv.setY(y);

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
        pathTransition.setNode(this.iv);
        pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
    }

    public ImageView getImageView() {
        return this.iv;
    }
    public PathTransition getPathTransition() {
        return this.pathTransition;
    }
    public String getName(){return this.name;}

    public void move(){
        this.pathTransition.play();
    }
}
