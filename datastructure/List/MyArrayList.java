package dataStructure.datastructure.List;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class MyArrayList<E> implements Iterable<E> {
    private static final int DEFAULT_CAPACITY = 10;
    private int size;
    private E[] items;

    public MyArrayList() {
        doClear();
    }

    private void doClear() {
        this.size = 0;
        ensureCapacity(DEFAULT_CAPACITY);
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public void trimToSize() {
        ensureCapacity(size());
    }

    public E get(int index) {
        if (index < 0 || index > size) {
            throw new ArrayIndexOutOfBoundsException();
        }
        return items[index];
    }

    public E set(int index, E newVal) {
        if (index < 0 || index > size) {
            throw new ArrayIndexOutOfBoundsException();
        }
        E old = items[index];
        items[index] = newVal;
        return old;
    }

    private void ensureCapacity(int newCapacity) {
        if (newCapacity < size) {
            return;
        }
        E[] old = items;
        items = (E[]) new Object[newCapacity];
        for (int i = 0; i < size(); i++) {
            items[i] = old[i];
        }
    }

    public boolean add(E x) {
        add(size(), x);
        return true;
    }

    public void add(int index, E x) {
        if (items.length == size()) {
            ensureCapacity(size() * 2 + 1);
        }
        for (int i = size; i > index; i--) {
            items[i] = items[i - 1];
        }
        items[index] = x;
        size++;
    }

    public E remove(int index) {
        E removeItem = items[index];
        for (int i = index; i < size() - 1; i--) {
            items[i] = items[i + 1];
        }
        size--;
        return removeItem;
    }

    @Override
    public Iterator<E> iterator() {
        return new ArrayListIterator();
    }

    private class ArrayListIterator implements Iterator<E> {

        private int current = 0;

        @Override
        public boolean hasNext() {
            return current < size();
        }

        @Override
        public E next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            return items[current++];
        }

        public void remove() {
            MyArrayList.this.remove(--current);
        }
    }
}
