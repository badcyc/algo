package dataStructure.sort;

public class QuickSort {
    public static <AnyType extends Comparable<? super AnyType>>
    void quickSort(AnyType[] a) {
        quickSort(a, 0, a.length - 1);
    }

    private static final int CUTOFF = 3;

    public static <AnyType extends Comparable<? super AnyType>>
    void quickSort(AnyType[] a, int left, int right) {
        if (left + CUTOFF <= right) {
            AnyType pivot = median3(a, left, right);
            int i = left, j = right - 1;
            for (; ; ) {
                while (a[++i].compareTo(pivot) < 0) {
                }
                while (a[--j].compareTo(pivot) > 0) {
                }
                if (i < j)
                    swapReference(a, i, j);
                else break;
            }
            swapReference(a, i, right - 1);
            quickSort(a, left, i - 1);        //sort small element
            quickSort(a, i + 1, right);        //sort large element
        } else
            insertionSort(a, left, right);
    }

    private static <AnyType extends Comparable<? super AnyType>>
    void insertionSort(AnyType[] a, int left, int right) {
        for (int p = left + 1; p <= right; p++) {
            AnyType tmp = a[p];
            int j;

            for (j = p; j > left && tmp.compareTo(a[j - 1]) < 0; j--)
                a[j] = a[j - 1];
            a[j] = tmp;
        }
    }

    private static <AnyType extends Comparable<? super AnyType>>
    AnyType median3(AnyType[] a, int left, int right) {
        int center = (left + right) / 2;
        if (a[center].compareTo(a[left]) < 0)
            swapReference(a, left, center);
        if (a[right].compareTo(a[left]) < 0)
            swapReference(a, right, left);
        if (a[center].compareTo(a[right]) < 0)
            swapReference(a, right, center);
        swapReference(a, center, right - 1);
        return a[right - 1];
    }

    public static <AnyType> void swapReference(AnyType[] a, int index1, int index2) {
        AnyType tmp = a[index1];
        a[index1] = a[index2];
        a[index2] = tmp;
    }

    private static <AnyType extends Comparable<? super AnyType>>
    void quickSelect(AnyType[] a, int left, int right, int k) {
        if (left + CUTOFF <= right) {
            AnyType pivot = median3(a, left, right);
            int i = left, j = right - 1;
            for (; ; ) {
                while (a[++i].compareTo(pivot) < 0) {
                }
                while (a[--j].compareTo(pivot) > 0) {
                }
                if (left < right)
                    swapReference(a, i, j);
                else break;
            }
            swapReference(a,i,right-1);   //restore pivot
            if (k<=i)
                quickSelect(a,left,i-1,k);
            else if (k>i+1)
                quickSelect(a,i+1,right,k);
        }
        else  //Do an insertion sort on the subarray
            insertionSort(a,left,right);
    }

}
