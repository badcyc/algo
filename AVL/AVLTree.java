package AVLtree.AVL;

import AVLtree.ITree;

public class AVLTree<T extends Comparable> implements ITree<T> {

    public AVLNode<T> root;

    @Override
    public boolean isEmpty() {
        return root==null;
    }

    @Override
    public int size() {
        return size(root);
    }
    public int size(AVLNode<T> node){
        if (node==null){
            return 0;
        }else {
            return size(node.left)+1+size(node.right);
        }
    }
    @Override
    public int height() {
        return height(root);
    }
    public int height(AVLNode<T> root){
        return root==null?-1:root.height;
    }

    @Override
    public String preOrder() {
        String sb=preOrder(root);
        if (sb.length()>0){
            sb=sb.substring(0,sb.length()-1);
        }
        return sb;
    }
    public String preOrder(AVLNode<T> root){
        StringBuilder stringBuilder=new StringBuilder();
        if (root!=null){
            stringBuilder.append(root.data).append(",");
            stringBuilder.append(preOrder(root.left));
            stringBuilder.append(preOrder(root.right));
        }
        return stringBuilder.toString();
    }

    @Override
    public String inOrder() {
        String sb=inOrder(root);
        if(sb.length()>0){
            //去掉尾部","号
            sb=sb.substring(0,sb.length()-1);
        }
        return sb;
    }
    private String inOrder(AVLNode<T> subtree){
        StringBuilder sb =new StringBuilder();
        if (subtree!=null) {
            //访问左子树
            sb.append(inOrder(subtree.left));
            //访问根结点
            sb.append(subtree.data).append(",");
            //访问右子树
            sb.append(inOrder(subtree.right));
        }
        return sb.toString();
    }
    @Override
    public String levelOeder() {
        //todo
        return null;
    }

    @Override
    public void insert(T data) {

        if (data==null){
            throw new RuntimeException("data can\'t not be null");
        }

    }

   /* private AVLNode<T> insert(T data,AVLNode<T>p){
        if (p==null){
            p=new AVLNode<T>(data);
        }else if (data.compareTo(p.data)<0){
            p.left=insert(data,p.left);
            if (height(p.left)-height(p.right)==2){
                if (data.compareTo(p.left.data)<0){
                    p=singleRotateLeft(p);
                }else {
                    p=doubleRotateWithLeft(p);
                }
            }
        }else if (data.compareTo(p.data)>0){
            p.right=insert(data,p.right);
            if (height(p.right)-height(p.left)==2){
                if (data.compareTo(p.right.data)<0){
                    p=doubleRotateWithRight(p);
                }else {
                    p=singleRotateRight(p);
                }
            }
        }
        p.height=Math.max(height(p.left),height(p.right))+1;
        return p;
    }
*/

    public AVLNode<T> insert(AVLNode<T> p,T data){
        if (p==null){
            p=new AVLNode<T>(data);
        }
        if (data.compareTo(p.data)<0){
            p.left=insert(p.left,data);
            if (height(p.left)-height(p.right)==2){
                if (data.compareTo(p.left.data)<0){
                    singleRotateRight(p);
                }else
                    doubleRotateWithLeft(p);
            }
        }else if (data.compareTo(p.data)>0){
            p.right=insert(p.right,data);
            if (height(p.right)-height(p.left)==2){
                if (data.compareTo(p.left.data)>0){
                    singleRotateLeft(p);
                }else
                    doubleRotateWithRight(p);
            }
        }
        p.height=Math.max(height(p.left),height(p.right))+1;
        return p;
    }
    @Override
    public void remove(T data) {
        if (data==null){
            throw new RuntimeException("data can\'t not be null ");
        }
        this.root=remove(data,root);
    }

    /**
     * 删除操作
     * @param data
     * @param p
     * @return
     */
    private AVLNode<T> remove(T data,AVLNode<T> p){

        if(p ==null)
            return null;

        int result=data.compareTo(p.data);

        //从左子树查找需要删除的元素
        if(result<0){
            p.left=remove(data,p.left);

            //检测是否平衡
            if(height(p.right)-height(p.left)==2){
                AVLNode<T> currentNode=p.right;
                //判断需要那种旋转
                if(height(currentNode.left)>height(currentNode.right)){
                    //LL
                    p=singleRotateLeft(p);
                }else{
                    //LR
                    p=doubleRotateWithLeft(p);
                }
            }

        }
        //从右子树查找需要删除的元素
        else if(result>0){
            p.right=remove(data,p.right);
            //检测是否平衡
            if(height(p.left)-height(p.right)==2){
                AVLNode<T> currentNode=p.left;
                //判断需要那种旋转
                if(height(currentNode.right)>height(currentNode.left)){
                    //RR
                    p=singleRotateRight(p);
                }else{
                    //RL
                    p=doubleRotateWithRight(p);
                }
            }
        }
        //已找到需要删除的元素,并且要删除的结点拥有两个子节点
        else if(p.right!=null&&p.left!=null){

            //寻找替换结点
            p.data=findMin(p.right).data;

            //移除用于替换的结点
            p.right = remove( p.data, p.right );
        }
        else {
            //只有一个孩子结点或者只是叶子结点的情况
            p=(p.left!=null)? p.left:p.right;
        }

        //更新高度值
        if(p!=null)
            p.height = Math.max( height( p.left ), height( p.right ) ) + 1;
        return p;
    }

    /**
     * 查找最小值结点
     * @param p
     * @return
     */
    private AVLNode<T> findMin(AVLNode<T> p){
        if (p==null)//结束条件
            return null;
        else if (p.left==null)//如果没有左结点,那么t就是最小的
            return p;
        return findMin(p.left);
    }

    @Override
    public T findMin() {
        return findMin(root).data;
    }

    @Override
    public T findMax() {
        return findMax(root).data;
    }

    /**
     * 查找最大值结点
     * @param p
     * @return
     */
    private AVLNode<T> findMax(AVLNode<T> p){
        if (p==null)
            return null;
        else if (p.right==null)//如果没有右结点,那么t就是最大的
            return p;
        return findMax(p.right);
    }


    @Override
    public boolean contains(T data) {
        return data != null && contain(data, root);
    }

    public boolean contain(T data , AVLNode<T> subtree){

        if (subtree==null)
            return false;

        int result =data.compareTo(subtree.data);

        if (result<0){
            return contain(data,subtree.left);
        }else if(result>0){
            return contain(data,subtree.right);
        }else {
            return true;
        }
    }

    @Override
    public void clear() {
        this.root=null;
    }
    /**
     * 左左单旋转(LL旋转) w变为x的根结点, x变为w的右子树
     * @param x
     * @return
     * */
    private AVLNode<T> singleRotateRight(AVLNode<T> x){
        //把w结点旋转为根结点
        AVLNode<T> w=  x.left;
        //同时w的右子树变为x的左子树
        x.left=w.right;
        //x变为w的右子树
        w.right=x;
        //重新计算x/w的高度
        x.height=Math.max(height(x.left),height(x.right))+1;
        w.height=Math.max(height(w.left),x.height)+1;
        return w;//返回新的根结点
    }

    /**
     * 右右单旋转(RR旋转) x变为w的根结点, w变为x的左子树
     * @return
     */
    private AVLNode<T> singleRotateLeft(AVLNode<T> w){

        AVLNode<T> x=w.right;

        w.right=x.left;
        x.left=w;

        //重新计算x/w的高度
        x.height=Math.max(height(x.left),w.height)+1;
        w.height=Math.max(height(w.left),height(w.right))+1;

        //返回新的根结点
        return x;
    }

    /**
     * 左右旋转(LR旋转) x(根) w y 结点 把y变成根结点
     * @return
     */
    private AVLNode<T> doubleRotateWithLeft(AVLNode<T> x){
        x.left=singleRotateLeft(x.left);
        return singleRotateRight(x);
    }

    /**
     * 右左旋转(RL旋转)
     * @param w
     * @return
     */
    private AVLNode<T> doubleRotateWithRight(AVLNode<T> w){
        w.right=singleRotateRight(w.right);
        return singleRotateLeft(w);
    }
}
