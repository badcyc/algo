package dataStructure.sort;

public class InsertionSort {
    public static <AnyType extends Comparable<? super AnyType>> void insertionSort(AnyType[] a) {
        int k;
        for (int i = 1; i < a.length; i++) {
            AnyType tmp = a[i];
            for (k = i; k > 0 && tmp.compareTo(tmp) < 0; k--) {
                a[k] = a[k - 1];
            }
            a[k] = tmp;
        }
    }
}
