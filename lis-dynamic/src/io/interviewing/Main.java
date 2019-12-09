package io.interviewing;

public class Main {

    public static void main(String[] args) {
	// write your code here
        int[] seq = new int[] {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
        Lis lis = new Lis(seq);
        lis.perform();
        dumpList(lis.getLIS());

        Lids lids = new Lids(seq);
        lids.perform();
        System.out.println("alternation - decreasing");
        dumpList(lids.getDec());
        System.out.println("alternation - increasing");
        dumpList(lids.getInc());

    }

    private static void dumpList (int[] l) {
        for (int i = 0; i < l.length; ++i) {
            System.out.printf("[%d]: %d\n", i, l[i]);
        }
    }
}
