package io.interviewing;

/**
 * Finds longest increasing-decreasing (or decreasing-increasing) sequence.
 */
public class Lids extends Lis {
    Lids(int[] sequence) {
        super(sequence);
        subseqDec = new int[sequence.length];
        subseqInc = new int[sequence.length];
    }
    private int[] subseqInc;
    private int[] subseqDec;

    public int[] getInc() {
        return subseqInc;
    }
    public int[] getDec() {
        return subseqDec;
    }

    private int compare(int indexA, int indexB) {
        return Integer.compare(sequence[indexA], sequence[indexB]);
    }
    public void perform() {
        //Инвариант
        //longest_increasing_subsequence[i]
        //это наибольшая длина подпоследовательности a_0...a_i.
        // в индексе j уже вычесленные штуки, посему j < i. если a[i] > a[j], условие выполнено.
        for(int i = 0; i < sequence.length; ++i) {
            int maxInc = 0;
            int maxDec = 0;
            for (int j = 0; j < i; ++j) {
                switch (compare(i, j)) {
                    case 1: // The current element > the last element. Next: decreasing
                        maxDec = maxDec > subseqInc[j] ? maxDec : subseqInc[j];
                        break;
                    case -1: // Next: increasing.
                        maxInc = maxInc > subseqDec[j] ? maxInc : subseqDec[j];
                        break;
                }
            }
            subseqDec[i] = 1 + maxDec;
            subseqInc[i] = 1 + maxInc;
        }
    }
}

