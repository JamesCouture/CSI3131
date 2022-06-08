public class Q1PrimePrinter implements Runnable {

    int max;

    public Q1PrimePrinter(int maxInt){

        max = maxInt;

    }


    @Override
    public void run() {

        int index = 2;
        while(index <= max){
            if (isPrime(index)){
                System.out.println(index);
            }
            index+=1;
        }
    }


    public boolean isPrime(int num){
        for(int i = 2; i < num; i++){
            if(num % i == 0){
                return false;
            }
        }
       return true; 
    }
    
}
