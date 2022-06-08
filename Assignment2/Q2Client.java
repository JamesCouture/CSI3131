public class Q2Client {
    public static void main(String args[]) throws InterruptedException{

        //Setting the Client object
        Q2Fibonacci fibonacci = new Q2Fibonacci(Integer.parseInt(args[0]));

        //Creating the thread
        Thread thread = new Thread(fibonacci);

        //Starting the thread
        thread.start();
        thread.join();

        System.out.println(fibonacci.fibonacciNumbers.toString());

    }
}
