import java.util.ArrayList;

public class ResponseToParse extends Response{
    public ResponseToParse(byte[] recv) {
        super(recv);
    }
    public ArrayList<Fish> GetFishes(){
        ArrayList<Fish> fishes = new ArrayList<Fish>();
        skipString();
        String name=new String();
        int x=0,y=0,xx=0,yy=0,z=0;
        while(!sentenceEnded()){
            name=popString();
            skipString();
            x=popInt('*');
            y=popInt(',');
            xx=popInt('*');
            yy=popInt(',');
            z=popInt(']');
            skipspace();
            Fish f = new Fish(name,x,y,xx,yy,z);
            fishes.add(f);
        }
        return fishes;
    }

    public ArrayList<ArrayList<Fish>> ls(){
        ArrayList<ArrayList<Fish>> states = new ArrayList<ArrayList<Fish>>();
        while(!responseEnded()){
            states.add(GetFishes());
        }
        return states;
    }

    public boolean getPing(int ping ){
        skipString();
        int pong =popInt();
        return ping == pong;
    }

    public String greetings(){
        String s1=new String("no");
        if(s1.equals(popString())){
            return null ; 
        }
        return popString();
    }

}