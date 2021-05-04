package aquarium.gui;

import javafx.animation.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.shape.CubicCurveTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

import java.awt.*;
import java.util.Random;

public class Fish {
    final private ImageView iv;
    private double duration;
    private Point destination;
    private PathTransition pathTransition;
    boolean atDestination;
    String name;

    public Fish(String name, int fish_width, int fish_height, Point position, Point destination, double duration){
        this.name = name;
        this.duration = duration;
        this.destination = destination;
        this.atDestination = false;
        this.iv = new ImageView();
        String ImagePath = "file:resources/images/" + name.split("_")[0] + ".png";
        System.out.println(ImagePath);
        this.iv.setImage(new Image(ImagePath));

        this.iv.setFitWidth(fish_width);
        this.iv.setFitHeight(fish_height);
        this.iv.setX(position.getX());
        this.iv.setY(position.getY());

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
    public String getFishType(){return this.name;}
    public Point getPosition(){return new Point((int)this.iv.getX(), (int)this.iv.getY());}

    public void move(){
        this.pathTransition.play();
    }

    public void move (int time_elapsed) {

        if (Math.abs(this.destination.getX()-this.iv.getX()) > 1.0 || Math.abs(this.destination.getY()-this.iv.getY()) > 1.0){
            this.iv.setX( this.iv.getX() + (this.destination.getX() - this.iv.getX())/(this.duration * 1000 / time_elapsed));
            this.iv.setY( this.iv.getY() + (this.destination.getY() - this.iv.getY())/(this.duration * 1000 / time_elapsed));
        }
        else {
            this.atDestination = true;
        }

    }

    public String getName() {
        return this.name;
    }
}
