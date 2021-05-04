package aquarium.parse;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.LinkedList;

public class ParseUserInput implements Runnable {
    final private BufferedReader stdIn;
    final private PrintWriter out;
    public static LinkedList<String> commandsList;

    public ParseUserInput(BufferedReader in, PrintWriter out) {
        this.stdIn = in;
        this.out = out;
        commandsList = new LinkedList<>();
    }

    @Override
    public void run() {
        String userInput;
        try {
            while ((userInput = stdIn.readLine()) != null) {
                commandsList.add(userInput);
                out.println(userInput);
                out.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static LinkedList<String> getListCommands() {
        return commandsList;
    }
}
