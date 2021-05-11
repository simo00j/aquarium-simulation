package aquarium.gui;

import javafx.animation.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.shape.CubicCurveTo;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

import java.awt.*;

public class Fish {
    final private ImageView iv;
    private Duration duration;
    private Point destination;
    final private PathTransition pathTransition;
    String name;

    public Fish(String name, int fish_width, int fish_height, Point position, Point destination, int duration){
        this.name = name;
        this.duration = Duration.millis(duration * 1000);
        this.destination = destination;
        this.iv = new ImageView();
        String ImagePath = "file:resources/images/" + name.split("_")[0] + ".png";
        this.iv.setImage(new Image(ImagePath));

        this.iv.setFitWidth(fish_width);
        this.iv.setFitHeight(fish_height);
        Path path = new Path();
        if (position != null){
            this.iv.setX(position.getX());
            this.iv.setY(position.getY());
            path.getElements().add(new MoveTo(position.getX(), position.getY()));
            path.getElements().add(new LineTo(destination.getX(), destination.getY()));
        }
        this.pathTransition = new PathTransition();
        this.pathTransition.setDuration(this.duration);
        this.pathTransition.setPath(path);
        this.pathTransition.setNode(this.iv);
        this.pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
    }

    public ImageView getImageView() {
        return this.iv;
    }

    public PathTransition getPathTransition() {
        return pathTransition;
    }

    public void move(){
        this.pathTransition.play();
    }

    public String getName() {
        return this.name;
    }

    public Duration getDuration() { return this.duration; }

    public Point getDestination() { return this.destination; }

    public void updateFish(Fish fish) {
        Path path = new Path();
        path.getElements().add(new MoveTo(this.destination.getX() , this.destination.getY()));
        this.destination = fish.getDestination();
        this.duration = fish.getDuration();
        path.getElements().add(new LineTo(this.destination.getX(), this.destination.getY()));
        this.pathTransition.setPath(path);
        this.pathTransition.setDuration(this.duration);
    }
}
