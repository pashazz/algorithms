package io.interviewing;

public class Lis extends LongestSequenceLength {
    protected int[] subsequence;
    protected int[] sequence;
    Lis(int[] sequence) {
        this.sequence = sequence;
        this.subsequence = new int[sequence.length];
    }

    public int []getLIS() {
        return subsequence;
    }
    public void perform() {
        //Инвариант
        //longest_increasing_subsequence[i]
        //это наибольшая длина подпоследовательности a_0...a_i.
        // в индексе j уже вычесленные штуки, посему j < i. если a[i] > a[j], условие выполнено.
        for(int i = 0; i < sequence.length; ++i) {
            int max = 0;
            for (int j = 0; j < i; ++j) {
                if (compareIndex(i, j)) {
                    if (subsequence[j] > max) {
                        max = subsequence[j];
                    }
                }
            }
            subsequence[i] = max + 1;
        }

    }


    @Override
    protected boolean compareIndex(int indexA, int indexB) {
        return sequence[indexA] > sequence[indexB];
    }



}
