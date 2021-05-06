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
                this.connection.logger.info("< " + scanned);
                if (scanned.startsWith("list")) {
                    if (connection.commandsList.getLast().equals("getFishesContinuously")) {
                        Parser.parseFishList(scanned, connection);
                    } else if (connection.commandsList.getLast().equals("getFishes")) {
                        Parser.parseGetFishes(scanned, connection);
                    }
                } else if (scanned.startsWith("bye") || scanned.startsWith("no greeting")) {
                    this.connection.endConnection();
                    System.exit(0);
                } else if (scanned.startsWith("greeting") || scanned.startsWith("pong")) {
                    Parser.parseGreeting(scanned);
                    connection.launch();
                } else if (scanned.startsWith("\t->OK")) {
                    this.connection.prompt.addResponse(scanned);
                } else if (scanned.startsWith("OK")) {
                    String command = this.connection.commandsList.getLast();
                    this.connection.prompt.addResponse(scanned);
                    if (command.startsWith("addFish")) {
                        Parser.parseAddFish(command, this.connection);
                    } else if (command.startsWith("delFish")) {
                        this.connection.delFish(command.split(" ")[1]);
                    } else if (command.startsWith("startFish")) {
                        this.connection.startFish(command.split(" ")[1]);
                    }
                } else if (scanned.startsWith("NOK")) {
                    this.connection.prompt.addResponse(scanned);
                }
            }
        }

        catch (IOException e) {
            connection.logger.severe("No server is listening port " + Config.properties.getProperty("controller-port"));
        }
    }
}
