package dataStructure.Heap;

import java.nio.BufferUnderflowException;

public class BinaryHeap<E extends Comparable<? super E>> {
    public BinaryHeap() {
        this(DEFAULT_CAPACITY);
    }

    public BinaryHeap(int capacity) {
        currentSize = 0;
        array = (E[]) new Comparable[capacity + 1];
    }

    public BinaryHeap(E[] items) {
        currentSize = items.length;
        array = (E[]) new Comparable[(currentSize * 2) * 11 / 10];
        int i = 1;
        for (E item : items)
            array[i++] = item;
        buildHeap();
    }

    private void buildHeap() {
        for (int i = currentSize / 2; i > 0; i--)
            percolateDown(i);
    }

    public void insert(E x) {
        if (currentSize == array.length - 1)
            enlargeArray(array.length * 2 + 1);

        //percolate up
        int hole = ++currentSize;
        for (array[hole] = x; x.compareTo(array[hole]) < 0; hole /= 2)
            array[hole] = array[hole / 2];
        array[hole] = x;
    }

    public E findMin() {
        if (isEmpty()) throw new BufferUnderflowException();
        return array[1];
    }

    public E deleteMin() {
        if (isEmpty()) throw new BufferUnderflowException();
        E minItem = findMin();
        array[1] = array[currentSize--];
        percolateDown(1);
        return minItem;
    }

    /**
     * 下滤
     *
     * @param hole
     */
    private void percolateDown(int hole) {
        int child;
        E temp = array[hole];
        for (; hole * 2 <= currentSize; hole = child) {
            child = hole * 2;
            if (child != currentSize && array[child + 1].compareTo(array[child]) < 0)
                child++;
            if (array[child].compareTo(temp) < 0)
                array[hole] = array[child];
            else break;
        }
        array[hole] = temp;
    }

    public boolean isEmpty() {
        return currentSize == 0;
    }

    public void makeEmpty() {
        currentSize = 0;
    }

    public static final int DEFAULT_CAPACITY = 10;

    private int currentSize;

    private E[] array;

    private void enlargeArray(int newSize) {
        E[] old = array;
        array = (E[]) new Comparable[newSize];
        for (int i = 0; i < old.length; i++) {
            array[i] = old[i];
        }
    }
}
