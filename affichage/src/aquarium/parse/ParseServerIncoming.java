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
        try {
            while (this.connection.client.getSocket().isConnected()) {
                final String scanned = this.connection.client.in.readLine();
                if (scanned.startsWith("list")) {
                    if (connection.commandsList.getFirst().equals("getFishesContinuously")) {
                        Parser.parseFishList(scanned, connection);
                    } else if (connection.commandsList.getFirst().equals("getFishes")) {
                        Parser.parseGetFishes(scanned, connection);
                    }
                } else if (scanned.startsWith("bye") || scanned.startsWith("no greeting")) {
                    System.out.println(scanned);
                    this.connection.endConnection();
                    System.exit(0);
                } else if (scanned.startsWith("greeting")) {
                    Parser.parseGreeting(scanned);
                } else if (scanned.startsWith("\t->OK")) {
                    this.connection.prompt.addResponse(scanned);
                } else if (scanned.startsWith("OK")) {
                    this.connection.commandsList.getFirst();
                    String command = this.connection.commandsList.getFirst();
                    if (command.startsWith("addFish")) {
                        Parser.parseAddFish(command, this.connection);
                    } else if (command.startsWith("delFish")) {
                        this.connection.delFish(command.split("\\s")[1]);
                    } else if (command.startsWith("startFish")) {
                        this.connection.startFish(command.split("\\s")[1]);
                    }
                }
            }
        }

        catch (IOException e) {
            System.out.println("No server is listening port " + Config.properties.getProperty("controller-port"));
        }
    }
}
