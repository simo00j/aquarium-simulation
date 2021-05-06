package aquarium.parse;

import aquarium.Config;
import aquarium.Connection;
import aquarium.gui.Fish;
import java.awt.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Parser {


    public static void parseGetFishes(String str, Connection connection) {
        String regex = "\\[(?<name>[a-zA-Z]+) at (?<positionX>\\d+)x(?<positionY>\\d+),(?<fishWidth>\\d+)x(?<fishHeight>\\d+),(?<duration>\\d+)]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("list ", ""));
        while (matcher.find()) {
            String name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"));
            int fish_height = Integer.parseInt(matcher.group("fishHeight"));
            int duration = Integer.parseInt(matcher.group("duration"));
            Point position = new Point(Integer.parseInt(matcher.group("positionX")), Integer.parseInt(matcher.group("positionY")));
            Fish fish = new Fish(name, fish_width, fish_height, position, position, duration);
            connection.addFish(fish);
        }
    }

    public static void parseFishList(String str, Connection connection) {
        String regex = "\\[(?<name>[a-zA-Z]+) at (?<destinationX>\\d+)x(?<destinationY>\\d+),(?<fishWidth>\\d+)x(?<fishHeight>\\d+),(?<duration>\\d+)]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("list ", ""));
        while (matcher.find()) {
            String name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"));
            int fish_height = Integer.parseInt(matcher.group("fishHeight"));
            Point destination = new Point(Integer.parseInt(matcher.group("destinationX")), Integer.parseInt(matcher.group("destinationY")));
            int duration = Integer.parseInt(matcher.group("duration"));
            Fish fish = new Fish(name, fish_width, fish_height, null, destination, duration);
            connection.updateFish(fish);
            connection.startFish(fish);
        }
    }

    public static void parseGreeting(String str) {
        Config.properties.setProperty("id", str.split("\\s")[1]);
    }

    public static void parseAddFish(String str, Connection connection) {

        String regex = "(?<name>[a-zA-Z_0-9]+) at (?<positionX>\\d+)x(?<positionY>\\d+), (?<fishWidth>\\d+)x(?<fishHeight>\\d+), ([a-zA-Z]+)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("addFish ", ""));
        while (matcher.find()) {
            String name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"));
            int fish_height = Integer.parseInt(matcher.group("fishHeight"));
            Point position = new Point(Integer.parseInt(matcher.group("positionX")), Integer.parseInt(matcher.group("positionY")));
            Fish fish = new Fish(name, fish_width, fish_height, position, position, 0);
            connection.addFish(fish);
        }

    }
}

