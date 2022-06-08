public class Q1Client {
    
    public static void main(String args[]){

        //Setting the Client object
        Q1PrimePrinter primePrinter = new Q1PrimePrinter(Integer.parseInt(args[0]));

        //Creating the thread
        Thread thread = new Thread(primePrinter);

        //Starting the thread
        thread.start();

    }
}
