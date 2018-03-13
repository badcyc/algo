package AVLtree.AVL;

public interface ITree<T extends Comparable> {
    boolean isEmpty();
    int size();
    int height();
    String preOrder();
    String inOrder();
    String levelOeder();
    void insert(T data);
    void remove(T data);
    T findMin();
    T findMax();
    boolean contains(T data)throws Exception;
    void clear();
}
