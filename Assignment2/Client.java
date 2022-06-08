public class Client {
    
    public static void main(String args[]){

        //Setting the Client object
        PrimePrinter primePrinter = new PrimePrinter(Integer.parseInt(args[0]));

        //Creating the thread
        Thread thread = new Thread(primePrinter);

        //Starting the thread
        thread.start();

    }
}
