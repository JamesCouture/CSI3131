import java.util.LinkedList;

public class Q2Fibonacci implements Runnable {

    LinkedList<Integer> fibonacciNumbers;
    int number;

    public Q2Fibonacci(int numberRecieved) {
        fibonacciNumbers = new LinkedList<>();
        number = numberRecieved;
    }

    @Override
    public void run() {

        if (number <= 0) {
            return;
        } else if (number == 1) {
            fibonacciNumbers.add(0);
        } else {

            int fib0 = 0;
            int fib1 = 1;
            int temp;

            fibonacciNumbers.add(fib0);
            fibonacciNumbers.add(fib1);

            for (int i = 0; i < number-2; i++) {

                fib0 += fib1;

                fibonacciNumbers.add(fib0);

                temp = fib0;
                fib0 = fib1;
                fib1 = temp;

            }
        }

    }

}