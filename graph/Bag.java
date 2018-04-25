package dataStructure.graph;

import org.jetbrains.annotations.NotNull;

import java.util.Iterator;

public class Bag<Item> implements Iterable<Item> {

    private Node<Item> first;
    private int n;

    private static class Node<Item> {
        private Item item;
        private Node<Item> next;
    }

    public Bag() {
        first = null;
        n = 0;
    }

    public boolean isEmpty(){
       return first==null;
    }
    public int size(){
        return n;
    }
    public void add(Item item){
        Node<Item> oldFirst=first;
        first=new Node<Item>();
        first.item=item;
        first.next=oldFirst;
        n++;
    }

    @NotNull
    @Override
    public Iterator<Item> iterator() {
        return new ListIterator<>(first);
    }
    private class ListIterator<Item> implements Iterator<Item>{
        private Node<Item> current;
        public ListIterator(Node<Item> first){
            current=first;
        }
        @Override
        public boolean hasNext() {
            return current==null;
        }

        @Override
        public Item next() {
            if (!hasNext()) throw new IllegalStateException();
            Item item = current.item;
            current=current.next;
            return item;
        }
    }
}
