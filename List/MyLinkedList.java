package dataStructure.List;

import java.security.AlgorithmConstraints;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class MyLinkedList<E> implements Iterable<E> {

    private Node<E> beginMarker;
    private Node<E> endMarker;
    private int size;
    private int modCount = 0;


    private static class Node<E> {
        public Node(E d, Node<E> p, Node<E> n) {
            data = d;
            prev = p;
            next = n;
        }

        public E data;
        public Node<E> prev;
        public Node<E> next;
    }

    public MyLinkedList() {
        doClear();
    }

    private void doClear() {
        beginMarker = new Node<>(null, null, null);
        endMarker = new Node<>(null, beginMarker, null);
        this.size = 0;
        this.modCount++;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public boolean add(E x) {
        add(size(), x);
        return true;
    }

    public void add(int index, E x) {
        addBefore(getNode(index, 0, size()), x);
    }

    public E get(int index) {
        return getNode(index).data;
    }

    public E set(int index, E newVal) {
        Node<E> p = getNode(index);
        E oldVal = p.data;
        p.data = newVal;
        return oldVal;
    }

    public E remove(int index) {
        return remove(getNode(index));
    }

    private void addBefore(Node<E> p, E x) {
        Node<E> newNode = new Node<>(x, p.prev, p);
        newNode.prev.next = newNode;
        p.prev = newNode;
        size++;
        modCount++;
    }

    private E remove(Node<E> p) {
        p.next.prev = p.prev;
        p.prev.next = p.next;
        size--;
        modCount++;
        return p.data;
    }

    private Node<E> getNode(int index) {
        return getNode(index, 0, size() - 1);
    }

    private Node<E> getNode(int index, int lower, int upper) {
        Node<E> p;
        if (index < lower || index > upper) {
            throw new IndexOutOfBoundsException();
        }
        if (index < size() / 2) {
            p = beginMarker;
            for (int i = 0; i < index; i++) {
                p = p.next;
            }
        } else {
            p = endMarker;
            for (int i = size(); i > index; i--) {
                p = p.prev;
            }
        }
        return p;
    }

    @Override
    public Iterator<E> iterator() {
        return new LinkedListIterator();
    }

    private class LinkedListIterator implements Iterator<E> {
        private Node<E> current = beginMarker.next;
        private int expectedModCount = modCount;                  // ①
        private boolean okToRemove = false;// ②

        @Override
        public boolean hasNext() {
            return current != endMarker;
        }

        @Override
        public E next() {
            if (modCount != expectedModCount) {
                throw new ConcurrentModificationException();
            }
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            E nextItem = current.data;
            current = current.next;
            okToRemove = true;
            return nextItem;
        }

        public void remove() {
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();
            if (!okToRemove) {
                throw new IllegalStateException();
            }
            MyLinkedList.this.remove(current.prev);
            expectedModCount++;
            okToRemove = false;
        }
    }
}

