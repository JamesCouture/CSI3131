
public class Q2Client {
    public static void main(String args[]) throws InterruptedException{
        
        if (args.length != 1) { // check there is only one argument
            throw new IllegalArgumentException("Exactly 1 parameter required!");
          }
        //Setting the Client object
        Q2Fibonacci fibonacci = new Q2Fibonacci(Integer.parseInt(args[0])); // parseInt throws exception if args[0] is not integer

        //Creating the thread
        Thread thread = new Thread(fibonacci);

        //Starting the thread
        thread.start();
        thread.join();

        System.out.println(fibonacci.fibonacciNumbers.toString());

    }
}
