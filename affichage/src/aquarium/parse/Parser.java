package aquarium.parse;

import aquarium.Config;
import aquarium.gui.Fish;

import java.awt.*;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Parser {

    Scanner scanner;
    private HashMap <String, Point> fishPositionsHashMap;

    public Parser(){
        scanner = new Scanner(System.in);
        fishPositionsHashMap = new HashMap<>();
    }


    public LinkedList<Fish> parseFishList(String str) {
        LinkedList<Fish> fishList = new LinkedList<>();
        String regex = "\\[(?<name>[a-zA-Z]+) at (?<destinationX>\\d+)x(?<destinationY>\\d+),(?<fishWidth>\\d+)x(?<fishHeight>\\d+),(?<duration>\\d+)\\]";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str.replace("list ", ""));
        while (matcher.find()) {
            String name = matcher.group("name");
            int fish_width = Integer.parseInt(matcher.group("fishWidth"));
            int fish_height = Integer.parseInt(matcher.group("fishHeight"));
            Point destination = new Point(0,0);
            int duration = Integer.parseInt(matcher.group("duration"));
            Point position = new Point(Integer.parseInt(matcher.group("destinationX")), Integer.parseInt(matcher.group("destinationY")));
            Fish fish = new Fish(name, fish_width, fish_height, position, destination, duration);
            fishList.add(fish);
        }
        return fishList;
    }

    public void parseGreeting(String str) {
        Config.properties.setProperty("id", str.split("\\s")[1]);
    }

    public void fillPositionsHashMap(HashMap <String,Point> hm){
        fishPositionsHashMap = hm;
    }



}

