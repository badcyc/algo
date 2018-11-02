package dataStructure.datastructure.HashTable;

import java.util.LinkedList;
import java.util.List;

public class SeparateChainingHashTable<E> {

    private static final int DEFAULT_TABLE_SIZE = 101;

    private List<E>[] lists;

    private int currentSize;

    private static int nextPrime(int n) {
        if (n % 2 == 0)
            n++;
        for (; !isPrime(n); n += 2)
            ;
        return n;
    }

    private static boolean isPrime(int n) {
        if (n == 2 || n == 3)
            return true;

        if (n == 1 || n % 2 == 0)
            return false;

        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        return true;
    }

    private void rehash() {
        List<E>[] oldLists = lists;
        lists = new List[nextPrime(2 * lists.length)];
        for (int j = 0; j < lists.length; j++) {
            lists[j] = new LinkedList<>();
        }
        currentSize = 0;
        for (int i = 0; i < oldLists.length; i++) {
            for (E item : oldLists[i])
                insert(item);
        }
    }

    public void insert(E x) {
        List<E> whichList = lists[myHash(x)];
        if (!whichList.contains(x)) {
            whichList.add(x);

            if (++currentSize > lists.length) {
                rehash();
            }
        }
    }

    public void remove(E x) {
        List<E> whichList = lists[myHash(x)];
        if (whichList.contains(x)) {
            whichList.remove(x);
            currentSize--;
        }
    }

    public boolean contains(E x) {
        List<E> whichList = lists[myHash(x)];
        return whichList.contains(x);
    }

    private int myHash(E x) {
        int hashVal = x.hashCode();

        hashVal %= lists.length;
        if (hashVal < 0) {
            hashVal += lists.length;
        }
        return hashVal;
    }

    public SeparateChainingHashTable() {
        this(DEFAULT_TABLE_SIZE);
    }

    public SeparateChainingHashTable(int size) {
        lists = new LinkedList[nextPrime(size)];
        for (int i = 0; i < lists.length; i++) {
            lists[i] = new LinkedList<>();
        }
    }

    public void makeEmpty() {
        for (int i = 0; i < lists.length; i++) {
            lists[i].clear();
            currentSize = 0;
        }
    }
    public static void main(String [] args){
        SeparateChainingHashTable<Integer> H=new SeparateChainingHashTable<>();
        long startTime=System.currentTimeMillis();
        final int NUMS=2000000;
        final int GAP=37;
        System.out.println("Checking... (no more output means success)");
        for( int i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            H.insert( i );
        for( int i = 1; i < NUMS; i+= 2 )
            H.remove( i );

        for( int i = 2; i < NUMS; i+=2 )
            if( !H.contains( i ) )
                System.out.println( "Find fails " + i );

        for( int i = 1; i < NUMS; i+=2 )
        {
            if( H.contains( i ) )
                System.out.println( "OOPS!!! " +  i  );
        }
        long endTime = System.currentTimeMillis( );
        System.out.println( "Elapsed time: " + (endTime - startTime) );
    }
}
