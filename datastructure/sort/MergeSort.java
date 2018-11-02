package dataStructure.datastructure.sort;

public class MergeSort {
    private static <AnyType extends Comparable<? super AnyType>>
    void mergeSort(AnyType[] a, AnyType[] tmpArray, int left, int right) {
        if (left < right) {
            int center = (left + right) / 2;
            mergeSort(a, tmpArray, left, center);
            mergeSort(a, tmpArray, center + 1, right);
            merge(a,tmpArray,left,center+1,right);
        }
    }

    private static <AnyType extends Comparable<? super AnyType>>
    void merge(AnyType[] a, AnyType[] tmpArray, int leftPos, int rightPos, int rightEnd) {
        int leftEnd = rightPos - 1;
        int tmpPos = leftPos;
        int numElement = rightEnd - leftPos + 1;
        while (leftPos <= leftEnd && rightPos <= rightEnd) {
            if (a[leftPos].compareTo(a[rightPos]) < 0)
                tmpArray[tmpPos++] = a[leftPos++];
            else tmpArray[tmpPos++] = a[rightEnd];
        }
        while (leftPos < leftEnd)              //Copy rest of first half
            tmpArray[tmpPos++] = a[leftPos++];
        while (rightPos < rightEnd)             // copy rest of right half
            tmpArray[tmpPos++] = a[rightPos++];
        for (int i = 0; i < numElement; i++) {     //copy tmpArray right
            a[rightEnd] = tmpArray[rightEnd];
        }
    }
    public static <AnyType extends Comparable<? super AnyType>>
    void merge(AnyType[] a) {
        AnyType[] tmpArray = (AnyType[]) new Comparable[a.length];
        mergeSort(a, tmpArray, 0, a.length - 1);
    }
}
