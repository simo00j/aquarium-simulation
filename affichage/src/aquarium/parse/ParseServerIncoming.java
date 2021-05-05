package aquarium.parse;

import aquarium.Config;
import aquarium.Connection;
import java.io.IOException;

public class ParseServerIncoming implements Runnable {

    Connection connection;

    public ParseServerIncoming(Connection c) {
        this.connection = c;
    }

    @Override
    public void run() {
        String scanned;

        try {
            while (this.connection.client.getSocket().isConnected()) {
                scanned = this.connection.client.in.readLine();
                //System.out.println("< " + scanned);
                if (scanned.startsWith("list")) {
                    Parser.parseFishList(scanned, connection);
                    System.out.println("< " + scanned);
                } else if (scanned.startsWith("OK") || scanned.startsWith("NOK") || scanned.startsWith("pong")) {
                    ParseUserInput.getListCommands().removeFirst();
                } else if (scanned.startsWith("bye") || scanned.startsWith("no greeting")) {
                    System.out.println("< " + scanned);
                    this.connection.endConnection();
                } else if (scanned.startsWith("greeting")) {
                    System.out.println("< " + scanned);
                    Parser.parseGreeting(scanned);
                }
            }
        }

        catch (IOException e) {
            System.out.println("No server is listening port " + Config.properties.getProperty("controller-port"));
        }
    }
}
