package aquarium.gui;

import javafx.animation.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

import java.awt.*;

public class Fish {
    final private ImageView iv;
    private Duration duration;
    private Point position;
    private Point destination;
    final private Path path;
    final private PathTransition pathTransition;
    String name;

    public Fish(String name, int fish_width, int fish_height, Point position, Point destination, int duration){
        this.name = name;
        this.duration = Duration.millis(duration * 1000);
        this.position = position;
        this.destination = destination;
        this.iv = new ImageView();
        String ImagePath = "file:resources/images/" + name.split("_")[0] + ".png";
        this.iv.setImage(new Image(ImagePath));

        this.iv.setFitWidth(fish_width);
        this.iv.setFitHeight(fish_height);
        this.iv.setX(position.getX());
        this.iv.setY(position.getY());

        this.path = new Path();
        this.path.getElements().add(new MoveTo(position.getX(), position.getY()));
        this.path.getElements().add(new LineTo(destination.getX(), destination.getY()));
        this.pathTransition = new PathTransition();
        this.pathTransition.setDuration(this.duration);
        this.pathTransition.setPath(path);
        this.pathTransition.setNode(this.iv);
        this.pathTransition.setOrientation(PathTransition.OrientationType.ORTHOGONAL_TO_TANGENT);
    }

    public ImageView getImageView() {
        return this.iv;
    }

    public void move(){
        this.pathTransition.play();
    }

    public String getName() {
        return this.name;
    }

    public Duration getDuration() { return this.duration; }

    public Point getPosition() { return this.position; }

    public Point getDestination() { return this.destination; }

    public void updateFish(Fish fish) {
        this.position = this.destination;
        this.destination = fish.getDestination();
        this.duration = fish.getDuration();
        this.path.getElements().add(new LineTo(destination.getX(), destination.getY()));
        this.pathTransition.setDuration(this.duration);
    }
}
