package dataStructure.Tree;

import java.nio.BufferUnderflowException;

public class BinarySearchTree<E extends Comparable<? super E>> {

    private BinaryNode<E> root;

    public BinarySearchTree() {
        root = null;
    }

    public void makeEmpty() {
        root = null;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public boolean contains(E x) {
        return contains(x, root);
    }

    public E findMin() {
        if (isEmpty()) throw new BufferUnderflowException();
        return findMin(root).element;
    }

    public E findMax() {
        if (isEmpty()) throw new BufferUnderflowException();
        return findMax(root).element;
    }

    public void insert(E x) {
        root = insert(x, root);
    }

    public void remove(E x) {
        root = remove(x, root);
    }

    public void printTree() {
        //todo
    }

    private boolean contains(E x, BinaryNode<E> t) {
        if (t == null) return false;
        int compareResult = x.compareTo(t.element);
        if (compareResult < 0) {
            return contains(x, t.left);
        } else if (compareResult > 0) {
            return contains(x, t.right);
        } else return true;
    }

    private BinaryNode<E> findMin(BinaryNode<E> t) {
        if (t == null) {
            return null;
        } else if (t.left == null) {
            return t;
        }
        return findMin(t.left);
    }

    private BinaryNode<E> findMax(BinaryNode<E> t) {
        if (t == null)
            return null;
        else if (t.right == null) {
            return t;
        }
        return findMax(t.right);
    }

    private BinaryNode<E> insert(E x, BinaryNode<E> t) {
        if (t == null) {
            return new BinaryNode<>(x, null, null);
        }
        int compareResult = x.compareTo(t.element);
        if (compareResult < 0)
            t.left = insert(x, t.left);
        else if (compareResult > 0)
            t.right = insert(x, t.right);
        else ;//duplicate;do nothing
        return t;
    }

    private BinaryNode<E> remove(E x, BinaryNode<E> t) {
        if (t == null)
            return t;
        int compareResult = x.compareTo(t.element);
        if (compareResult < 0)
            t.left = remove(x, t.left);
        else if (compareResult > 0)
            t.right = remove(x, t.right);
        else if (t.left != null && t.right != null) {
            t.element = findMin(t.right).element;
            t.right = remove(t.element, t.right);  //核心代码
        } else
            t = (t.left != null) ? t.left : t.right;
        return t;
    }

    private void printTree(BinaryNode<E> t) {
        //todo
    }


    //嵌套类
    private static class BinaryNode<E> {
        E element;
        BinaryNode<E> left;
        BinaryNode<E> right;

        BinaryNode(E element) {
            this(element, null, null);
        }

        BinaryNode(E element, BinaryNode<E> lt, BinaryNode<E> rt) {
            this.element = element;
            left = lt;
            right = rt;
        }
    }
}
