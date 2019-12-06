package io.interviewing;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
	// write your code here
        int[] array = {4, 6, 1, 100, -20};
        quicksort(array);
        System.out.println(Arrays.toString(array));
    }




    // 1. Choose a pivot - any element of the array
    // 2. PARTITIONING
    // Make sure that any element lesser than the pivot is to the left, and any element greater than the pivot is to the right
    // 3. DIVIDE
    // Find out where the pivot is and repeat the function on the array parts to the left and to the right of the pivot
    private static void quicksort(int[] a, int startIndex, int endIndex) {
        if (startIndex >= endIndex) {
            return;
        }
        int pivotIndex = partition(a, startIndex, endIndex);
        quicksort(a, startIndex, pivotIndex - 1);
        quicksort(a, pivotIndex + 1, endIndex);

    }

    /**
     * Does partitioning
     * @param a  | 7 | 2 | 1 | 6 | 8 | 5 | 3 | *4*
     * @param startIndex
     * @param endIndex
     * Makes sure that the a is | 2 | 1 | 3| *4* | 8 | 5| 7 | 6 if *4* is chosen as the pivot
     * uses choosePivotIndex as the pivot chooser
     * @return pivot index
     *
     * We make a variable of so-called partitionIndex.
     * The invariant is that for any i < partitionIndex, a[i] < pivot.
     * So we loop all the array and if a[i] < pivot, then swap (a[i], a[partitionIndex] and partitionIndex++;
     * So it'd look like this.
     * | 7 <- PI <- i | 2 | 1 | *6* | 8 | 5 | 3 | 4
     *
     * Step 1: partitionIndex (PI) = 0, i = 0
     * 7 >= 6 -> | 7 <- PI  | 2 <- i | 1 | *6* | 8 | 5 | 3 | 4
     * Step 2: partitionIndex (PI) = 0, i = 1
     * 2 < 6 -> | 2  |  7 <- PI | 1 <- i  | *6* | 8 | 5 | 3 | 4
     * Step 3: partitionIndex (PI) = 1, i = 2
     * 1 < 6 -> | 2  |  1 | 7 <- PI  | *6* <- i | 8 | 5 | 3 | 4
     * Step 4: partitionIndex (PI) = 2, i = 3
     * 6 >= 6 -> | 2  |  1 | 7 <- PI  | *6*  | 8 <- i | 5 | 3 | 4
     *  Step 5: partitionIndex (PI) = 2, i = 4
     *  8 >= 6 -> | 2  |  1 | 7 <- PI  | *6*  | 8  | 5 <- i | 3 | 4
     *  Step 6: partitionIndex (PI) = 2, i = 5
     *  5 < 6 -> | 2  |  1 | 5 | *6* <- PI  | 8  | 7 | 3 <- i  | 4
     *  Step 7: partitionIndex (PI) = 3, i = 6
     *  3 < 6 -> | 2  |  1 | 5 | 3  | 8 <- PI | 7 | *6*  | 4 <- i
     *  Step 7: partitionIndex (PI) = 4, i = 7
     *  4 < 6 ->  | 2  |  1 | 5 | 3  | 4  | 7 <-PI | *6*  | 8 |
     *  Step 8: Reached end of the loop, do final swap of pivot and a[pivotIndex]
     *   | 2  |  1 | 5 | 3  | 4  | *6* <-PI | 7  | 8 |
     *  Well done!
     */
    protected static int partition(int [] a, int startIndex, int endIndex) {
        int pivotIndex = choosePivotIndex(startIndex, endIndex);
        int partitionIndex = 0;
        int pivot = a[pivotIndex];
        for (int i = 0; i < a.length; ++i) {
            if (a[i] < pivot) {
                //Do the swap thing
                if (i != partitionIndex) {
                    int temp = a[i];
                    a[i] = a[partitionIndex];
                    a[partitionIndex] = temp;
                    // If pivot index and partition index are the same,
                    // then make sure to update the pivot index as a[partitionIndex] as been swapped with i
                    if (pivotIndex == partitionIndex) {
                        pivotIndex = i;
                    }
                }
                partitionIndex++;
            }
        }
        // After we exited the loop make sure that the pivot is at a[partitionIndex] - swap if necessary.
        if (pivotIndex != partitionIndex) {
            int temp = a[partitionIndex];
            a[partitionIndex] = a[pivotIndex];
            a[pivotIndex] = temp;
        }
        return partitionIndex; // this is the current location of the pivot
    }
    protected static int choosePivotIndex (int min, int max) {
        return max;
    }
    public static void quicksort(int [] array) { //in-place
        quicksort(array, 0, array.length - 1);
    }

}
