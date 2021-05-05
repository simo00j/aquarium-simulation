package aquarium.parse;

import aquarium.Connection;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;

public class ParseUserInput implements Runnable {
    final private BufferedReader stdIn;
    public static LinkedList<String> commandsList;
    final private Connection connection;

    public ParseUserInput(BufferedReader in, Connection c) {
        this.stdIn = in;
        this.commandsList = new LinkedList<>();
        this.connection = c;
    }

    @Override
    public void run() {
        String scanned;
        try {
            while ((scanned = stdIn.readLine()) != null) {
                commandsList.add(scanned);
                if (scanned.startsWith("addFish")){
                    Parser.parseAddFish(scanned, this.connection);
                }
                this.connection.client.out.println(scanned);
                this.connection.client.out.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static LinkedList<String> getListCommands() {
        return commandsList;
    }
}
