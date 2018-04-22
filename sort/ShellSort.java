package dataStructure.sort;

public class ShellSort {
    //         3 4 5 2 3 4 7 8  1 4
//(gap=5)->3 4 5 1 3 4 7 8  2 4
//(gap=2)->2 1 3 4 3 4 5 4  7 8
//(gap=1)->1 2 3 3 4 4 4 5  7 8
    public static <AnyType extends Comparable<? super AnyType>> void shellsort(AnyType[] a) {
        int j;
        for (int gap = a.length; gap > 0; gap /= 2) {
            for (int i = gap; i < a.length; i++) {
                AnyType tmp = a[i];
                for (j = i; j >= gap && tmp.compareTo(a[j - gap]) < 0; j -= gap)
                    a[j] = a[j - gap];
                a[j] = tmp;
            }
        }
    }
}
