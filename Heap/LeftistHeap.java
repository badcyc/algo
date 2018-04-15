package dataStructure.Heap;

import java.nio.BufferUnderflowException;

public class LeftistHeap<E extends Comparable<? super E>> {

    private LeftistNode<E> root;

    public LeftistHeap() {
        root = null;
    }

    public void merge(LeftistHeap<E> rhs) {
        if (this == rhs) {
            return;
        }
        root = merge(root, rhs.root);
        rhs.root = null;
    }

    private LeftistNode<E> merge(LeftistNode<E> h1, LeftistNode<E> h2) {
        if (h1 == null) return h2;
        if (h2 == null) return h1;
        if (h1.element.compareTo(h2.element) < 0)
            return merge1(h1, h2);
        else return merge1(h2, h1);
    }

    private LeftistNode<E> merge1(LeftistNode<E> h1, LeftistNode<E> h2) {
        if (h1.left == null)
            h1.left = h2;
        else {
            h1.right = merge(h1.right, h2);
            if (h1.left.npl < h1.right.npl)
                swapChildren(h1);
            h1.npl = h1.right.npl + 1;
        }
        return h1;
    }

    private static <E> void swapChildren(LeftistNode<E> t) {
        LeftistNode<E> tmp = t.left;
        t.left = t.right;
        t.right = tmp;
    }

    public E findMin() {
        if (isEmpty()) throw new BufferUnderflowException();
        return root.element;
    }

    public void insert(E x) {
        root = merge(new LeftistNode<>(x), root);
    }

        public E deleteMin() {
            if (isEmpty())
                throw new BufferUnderflowException();
            E minItem = root.element;
            root = merge(root.left, root.right);
            return minItem;
        }

    public boolean isEmpty() {
        return root == null;
    }

    private static class LeftistNode<E> {
        LeftistNode(E element) {
            this(element, null, null);
        }

        LeftistNode(E element, LeftistNode lt, LeftistNode rt) {
            this.element = element;
            left = lt;
            right = rt;
            npl = 0;
        }

        E element;
        LeftistNode<E> left;
        LeftistNode<E> right;
        int npl;
    }
}
