public class Q1Client {
    
    public static void main(String args[]){

        if (args.length != 1) { // check there is only one argument
            throw new IllegalArgumentException("Exactly 1 parameter required!");
          }

        //Setting the Client object
        Q1PrimePrinter primePrinter = new Q1PrimePrinter(Integer.parseInt(args[0])); // parseInt throws exception if args[0] is not integer

        //Creating the thread
        Thread thread = new Thread(primePrinter);

        //Starting the thread
        thread.start();

    }
}
