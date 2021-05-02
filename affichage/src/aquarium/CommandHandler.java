import java.util.ArrayList;
import java.util.Arrays;
public class CommandHandler {
    public  CommandHandler (String sent , byte[] received){
        Character[]charToParse = {'l','p','h','g'};
        ArrayList<Character> toParse = new ArrayList<Character>();
        toParse.addAll(Arrays.asList(charToParse));
        if (toParse.contains(sent.charAt(0)) && !sent.contains("log")){
            ResponseToParse response = new ResponseToParse(received);
            switch(sent.charAt(0)){
                case 'p':
                    String a = sent.replaceAll("[^0-9]", ""); 
                    boolean b = response.getPing(Integer.parseInt(a));
                    if (b){
                        //treat good ping
                    }
                    else {
                        //treat no match ping
                    } 
                    break;
                case 'h':
                    String name =response.greetings();
                    if (name!=null){
                        // treat no greeting
                    }
                    else{
                        //treat greeting
                    }
                    break ;
                case 'g':
                    if (sent.contains("Continuously")){
                        //continuously
                    }
                    else{
                        ArrayList<Fish> fishes = response.GetFishes();
                        //treat output
                    }
                    break;
                default:
                    ArrayList<ArrayList<Fish>> states = response.ls();
                    //treat output

            }        
        }
        else{ 
            response = new ResponseNotToParse(received);
        } 
    }
}
