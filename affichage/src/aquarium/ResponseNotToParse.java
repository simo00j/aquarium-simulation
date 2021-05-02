public class ResponseNotToParse extends Response{
    public ResponseNotToParse(byte[] recv){
        super(recv);
    }

    public void keeplog(){
        String msg = new String(this.getData());
        //keep log 
    }
    
}
