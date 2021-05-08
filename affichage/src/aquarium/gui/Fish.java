package aquarium.gui;

import aquarium.Config;
import javafx.animation.*;
import javafx.application.Platform;
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
    private Point destination;
    private Path path;
    final private PathTransition pathTransition;
    String name;

    public Fish(String name, int fish_width, int fish_height, Point position, Point destination, int duration){
        this.name = name;
        this.duration = Duration.millis(duration * 1000);
        this.destination = destination;
        this.iv = new ImageView();
        String ImagePath = "file:resources/images/" + name.split("_")[0] + ".png";
        this.iv.setImage(new Image(ImagePath));

        this.iv.setFitWidth((double)fish_width * Integer.parseInt(Config.properties.getProperty("viewer_width")) / 100);
        this.iv.setFitHeight((double)fish_height * Integer.parseInt(Config.properties.getProperty("viewer_height")) / 100);
        this.path = new Path();
        if (position != null){
            this.iv.setX(position.getX() * Integer.parseInt(Config.properties.getProperty("viewer_width")) / 100);
            this.iv.setY(position.getY() * Integer.parseInt(Config.properties.getProperty("viewer_height")) / 100);
            this.path.getElements().add(new MoveTo(position.getX() * Integer.parseInt(Config.properties.getProperty("viewer_width")) / 100, position.getY() * Integer.parseInt(Config.properties.getProperty("viewer_height")) / 100));
            this.path.getElements().add(new LineTo(destination.getX() * Integer.parseInt(Config.properties.getProperty("viewer_width")) / 100, destination.getY() * Integer.parseInt(Config.properties.getProperty("viewer_height")) / 100));
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

    public void move(){
        this.pathTransition.play();
    }

    public String getName() {
        return this.name;
    }

    public Duration getDuration() { return this.duration; }

    public Point getDestination() { return this.destination; }

    public void updateFish(Fish fish) {
        this.path = new Path();
        this.path.getElements().add(new MoveTo(destination.getX() * Integer.parseInt(Config.properties.getProperty("viewer_width")) / 100, destination.getY() * Integer.parseInt(Config.properties.getProperty("viewer_height")) / 100));
        this.destination = fish.getDestination();
        this.duration = fish.getDuration();
        this.path.getElements().add(new LineTo(destination.getX(), destination.getY()));
        this.pathTransition.setPath(this.path);
        this.pathTransition.setDuration(this.duration);
    }
}
