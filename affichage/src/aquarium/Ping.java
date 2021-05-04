package aquarium;

import aquarium.parse.ParseUserInput;

import java.io.PrintWriter;
import java.util.LinkedList;

public class Ping implements Runnable {
    public final PrintWriter out;
    public Ping(PrintWriter out) {
        this.out = out;
    }

    @Override
    public void run() {
        try {
            String pingString = new String("ping " + Config.properties.getProperty("controller-port"));
            while (true){
                synchronized (this.out) {
                    Thread.sleep (Integer.parseInt(Config.properties.getProperty("display-timeout-value")));
                    this.out.println(pingString);
                    ParseUserInput.getListCommands().add(pingString);
                    this.out.flush();
                }
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
