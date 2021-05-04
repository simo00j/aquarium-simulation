package aquarium.parse;

import aquarium.Config;
import aquarium.Connection;
import aquarium.gui.Fish;

import java.io.IOException;
import java.util.LinkedList;

public class ParseServerIncoming implements Runnable {

    Connection connection;

    public ParseServerIncoming(Connection c) {
        this.connection = c;
    }

    @Override
    public void run() {
        String scanned;
        Parser p = new Parser();

        try {
            while (true) {
                scanned = this.connection.client.in.readLine();
                //System.out.println("< " + scanned);
                if (scanned.startsWith("list")) {
                    LinkedList<Fish> fishList = p.parseFishList(scanned);
                    fishList.forEach(f -> this.connection.addFish(f));
                } else if (scanned.startsWith("OK") || scanned.startsWith("NOK") || scanned.startsWith("pong")) {
                    ParseUserInput.getListCommands().removeFirst();
                } else if (scanned.startsWith("bye") || scanned.startsWith("no greeting")) {
                    this.connection.endConnection();
                } else if (scanned.startsWith("greeting")) {
                    p.parseGreeting(scanned);
                }
            }
        }

        catch (IOException e) {
            System.out.println("No server is listening port " + Config.properties.getProperty("controller-port"));
        }
    }
}
