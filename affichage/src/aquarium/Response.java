
import java.util.ArrayList;
import java.util.Arrays;

public class Response {
    private int length;
    private int index;
    private byte[] data;

    public Response(byte[] recv) {
        this.data = recv;
        this.index = 0;
        this.length = data.length;
    }

    public int length(){
        return length;
    }

    public byte[] getData(){
        return data;
    }

    public void skipString(){
        popString();
    }
    
    public void skipspace(){
        char c = (char) data[index];
        if(c == ' ')
            index++;
    }

    public boolean sentenceEnded(){

        return data[index]=='\n';
    }

    public boolean responseEnded() {
        return index == length-1; 
    }

    public String popString() {
        return new String(pop(' '));
    }

    public int popInt(char c) {
        String s = new String(pop(c));
        return Integer.parseInt(s);
    }

    public int popInt(){
        String s = new String(pop(' '));
        return Integer.parseInt(s);
    }

    public byte[] popbytes(char c) {
        return pop(c);
    }
    
    public byte[] pop(char c){
        ArrayList<Byte> array = new ArrayList<Byte>();
        for (; index < data.length; index++) {
            if (data[index] == c ) {
                index++;
                break;
            }
            if (data[index] == '[' || data[index] == ']') {
                continue;
            }
            array.add(data[index]);
        }
        byte[] r = new byte[array.size()];
        for (int i = 0; i < array.size(); i++) {
            r[i] = array.get(i);
        }
        return r;
    }

}







