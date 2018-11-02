package dataStructure.datastructure.AVL;
import java.nio.BufferUnderflowException;

public class AvlTree<E extends Comparable<? super E>> {

    private AvlNode<E> root;

    public AvlTree() {
        root = null;
    }

    public void insert(E x) {
        root=insert(x,root);
    }

    public void remove(E x) {
        root=remove(x,root);
    }


    public void makeEmpty() {
        root = null;
    }

    public boolean contains(E x) {
        return contains(x, root);
    }

    private boolean contains(E x, AvlNode<E> t) {
        while (t != null) {
            int compareResult = x.compareTo(t.element);
            if (compareResult < 0) {
                t = t.left;
            } else if (compareResult > 0) {
                t = t.right;
            } else return true;
        }
        return false;
    }

    public E findMin() {
        if (isEmpty()) throw new BufferUnderflowException();
        return findMin(root).element;
    }

    private AvlNode<E> findMin(AvlNode<E> t) {
        if (t == null) {
            return t;
        }
        while (t.left != null) t = t.left;
        return t;
    }

    public E findMax() {
        if (root == null) throw new BufferUnderflowException();
        return findMax(root).element;
    }

    private AvlNode<E> findMax(AvlNode<E> t) {
        if (t == null) return t;
        while (t.right != null) t = t.right;
        return t;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public void printTree() {
        printTree(root);
    }

    private void printTree(AvlNode t) {
        if (t == null) return;
        System.out.println(t.element);
        printTree(t.left);
        printTree(t.right);
    }

    private AvlNode<E> remove(E x, AvlNode<E> t) {
        if (t==null)return t;
        int compareResult=x.compareTo(t.element);
        if (compareResult>0)
            t=remove(x,t.right);
        else if (compareResult<0)
            t=remove(x,t.left);
        else if (t.left!=null&&t.right!=null){
            t.element=findMin(t.right).element;
            t.right=remove(t.element,t.right);
        }else
            t=(t.left!=null)?t.left:t.right;
        return balance(t);
    }

    private static final int ALLOWED_IMBLANCE = 1;

    private AvlNode<E> balance(AvlNode<E> t) {
        if (t == null) return t;
        if (height(t.left) - height(t.right) > ALLOWED_IMBLANCE)
            if (height(t.left.left) >= height(t.left.right))
                t = rotateWithLeftChild(t);
            else
                t = doubleWithLeftChild(t);
        else if (height(t.right) - height(t.left) > ALLOWED_IMBLANCE)
            if (height(t.right.right) >= height(t.right.left))
                t = rotateWithRightChild(t);
            else
                t = doubleWithRightChild(t);
        t.height = Math.max(height(t.left), height(t.right)) + 1;
        return t;
    }

    public void checkBalance() {
        checkBalance(root);
    }

    private int checkBalance(AvlNode<E> t) {
        if (t == null) return -1;
        if (t != null) {
            int h1 = checkBalance(t.left);
            int hr = checkBalance(t.right);
            if (Math.abs(height(t.left) - height(t.right)) > 1 ||
                    height(t.left) != h1 || height(t.right) != hr) {
                System.out.println("OOPS");
            }
        }
        return height(t);
    }

    private AvlNode<E> insert(E x, AvlNode<E> t) {
        if (t==null)
            return new AvlNode<>(x,null,null);
        int compareResult=x.compareTo(t.element);
        if (compareResult>0)
            t=insert(x,t.right);
        else if (compareResult<0)
            t=insert(x,t.left);
        else ;
        return balance(t);
    }

    private int height(AvlNode<E> t) {
        if (t == null) return -1;
        return t.height;
    }

    private AvlNode<E> rotateWithLeftChild(AvlNode<E> k2) {
        AvlNode<E> lChild = k2.left;
        k2.left = lChild.right;
        lChild.right = k2;
        k2.height = Math.max(height(k2.left), height(k2.right)) + 1;
        lChild.height = Math.max(height(lChild.left), k2.height) + 1;
        return lChild;
    }

    private AvlNode<E> rotateWithRightChild(AvlNode<E> k2) {
        AvlNode<E> rChild = k2.right;
        k2.right = rChild.left;
        rChild.left = k2;
        k2.height = Math.max(height(k2.left), height(k2.right)) + 1;
        rChild.height = Math.max(height(rChild.right), k2.height) + 1;
        return rChild;
    }

    private AvlNode<E> doubleWithLeftChild(AvlNode<E> k3) {
        k3.left = rotateWithRightChild(k3.left);
        return rotateWithLeftChild(k3);
    }

    private AvlNode<E> doubleWithRightChild(AvlNode<E> k1) {
        k1.right = rotateWithLeftChild(k1.right);
        return rotateWithRightChild(k1);
    }

    private static class AvlNode<E> {
        // Constructors
        AvlNode(E theElement) {
            this(theElement, null, null);
        }

        AvlNode(E theElement, AvlNode<E> lt, AvlNode<E> rt) {
            element = theElement;
            left = lt;
            right = rt;
            height = 0;
        }

        E element;      // The data in the node
        AvlNode<E> left;         // Left child
        AvlNode<E> right;        // Right child
        int height;       // Height
    }
}
