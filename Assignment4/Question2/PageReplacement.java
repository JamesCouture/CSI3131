import java.util.*;
import java.util.LinkedList;
import java.util.Queue;
public class PageReplacement {
    public static void main(String[] args) {

        // create instance of Random class   
        Random rand = new Random(); 

        int[] pageRefString = new int[15]; // page reference string is set to a default length of 15

        for (int i = 0; i < 15 ; i++){
            // Generate random integers in range 0 to 9   
            int rand_int = rand.nextInt(10);  
            pageRefString[i] = rand_int;
             
        }
        int numOfframes = rand.nextInt(7)+1; // make frames a random number between 1 and 7
        System.out.println("frames: "+ numOfframes);

        System.out.println("page reference string: " + Arrays.toString(pageRefString));
        System.out.println("Total number of faults for FIFO: " + FIFOfaults(pageRefString, numOfframes));
        System.out.println("Total number of faults for LRU: " + LRUfaults(pageRefString, numOfframes));

    }

    public static int FIFOfaults(int[] refString, int numframes) {
        // create memory in queue data structure with length = # of frames
        System.out.println("===============================FIFO===============================");
        int faultCounter = 0;
        Queue<Integer> memory = new LinkedList<Integer>();
        for (int i = 0; i < refString.length ; i++) {
            int pageAddress = refString[i];
            
            //Determining if there is a free spot, if a page has to be replaced or if page is already in memory
            if (memory.contains(pageAddress)) {
                System.out.println("Try Page address "+pageAddress+ ". Already in frame: "+ memory);
                continue;
            } else if (memory.size() < numframes ) { // if still space in frame then add to frame; no fault
                memory.add(pageAddress);
                System.out.println("Try Page address "+pageAddress+ ". FAULT, added to frame: "+ memory);
                faultCounter++;
                continue;
            } else {
                int removed = memory.poll();
                memory.add(pageAddress);
                System.out.println("Try Page address "+pageAddress+ ". FAULT, removed "+removed+": "+ memory);
                faultCounter++;
            
            }
        }
        return faultCounter;
    }

    public static int LRUfaults(int[] refString, int frames) {
        System.out.println("===============================LRU===============================");
        int faultCounter = 0;
        Queue<Integer> memory = new LinkedList<Integer>();
        for (int i = 0; i < refString.length ; i++) {
            int pageAddress = refString[i];
            //Determining if there is a free spot, if a page has to be replaced or if page is already in memory
            if (memory.contains(pageAddress)) {
                memory.remove(pageAddress);
                memory.add(pageAddress); // remove then put at front so it is most recently used
                System.out.println("Try Page address "+pageAddress+ ". Already in frame: "+ memory);
                continue;
            } else if (memory.size() < frames ) { // if still space in frame then add to frame; no fault
                memory.add(pageAddress);
                System.out.println("Try Page address "+pageAddress+ ". FAULT, added to frame: "+ memory);
                faultCounter++;
            } else {
                int removed = memory.poll();
                memory.add(pageAddress); // remove the least recently used
                System.out.println("Try Page address "+pageAddress+ ". FAULT, removed "+removed+": "+ memory);
                // System.out.println("FAULT, removed "+removed+ " : Page address "+pageAddress+ " added: "+ memory);
                faultCounter++;
            }
        }
        return faultCounter;
    }
    
}
