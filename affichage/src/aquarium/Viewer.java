package aquarium;

public class Viewer {
    String name;
    private int viewer_x;
    private int viewer_y;
    int viewer_width;
    int viewer_height;
    String backgroundColor;

    Viewer(String name, int viewer_x, int viewer_y, int viewer_width, int viewer_height){
        this.name = name;
        this.viewer_x = viewer_x;
        this.viewer_y = viewer_y;
        this.viewer_width = viewer_width;
        this.viewer_height = viewer_height;
        this.backgroundColor = "black";
    }

    public String getName(){return name;}

    public int getWidth() {
        return viewer_width;
    }

    public int getHeight() {
        return viewer_height;
    }
}
