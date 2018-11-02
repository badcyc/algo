package dataStructure.datastructure.AVL1;

public class AVLNode<T extends Comparable> {
    public AVLNode<T> left;
    public AVLNode<T> right;
    public T data;
    public int height;
    public AVLNode(T data){
        this(data,null,null);
    }
    public AVLNode(T data,AVLNode<T> left,AVLNode<T> right){
        this(data,left,right,0);
    }
    public AVLNode(T data,AVLNode<T> left,AVLNode<T> right,int height){
        this.left=left;
        this.right=right;
        this.data=data;
        this.height=height;
    }


}
