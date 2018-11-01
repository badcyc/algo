package dataStructure.DepthFirstSearch;

import java.util.Stack;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-11-01 15:59
 **/
class TreeNode {
    int val;
    TreeNode left = null;
    TreeNode right = null;

    TreeNode(int x) {
        val = x;
    }
}

public class SameTree {
    public boolean isSameTree(TreeNode p, TreeNode q) {
        return isEqual2(p, q);
    }

    /**
     * @Description: 垃圾算法
     * @Param: [p, q]
     * @return: boolean
     * @Author: Yichao Chen
     * @Date: 18-11-1
     * @Time: 下午4:48
     **/
    private boolean isEqual(TreeNode p, TreeNode q) {
        boolean result;
        if (p != null) {
            if (q == null || (p.val != q.val)) return false;
            if (p.left != null) {
                if (q != null && q.left != null) {
                    if (p.left.val == q.left.val) {
                        result = isEqual(p.left, q.left);
                        if (!result) {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else
                    return false;
            }
            if (p.right != null) {
                if (q != null && q.right != null) {
                    if (p.right.val == q.right.val) {
                        result = isEqual(p.right, q.right);
                        if (!result)
                            return false;

                    } else {
                        return false;
                    }

                } else
                    return false;
            }
            if (q == null || (p.left == null && q.left != null) || (p.right == null && q.right != null)) return false;
        } else {
            if (q != null)
                return false;
        }
//        if (q.right!=null)return false;
        return true;
    }

    /**
     * @Description: 虽然代码简洁多了，但是复杂度依旧高
     * @Param: [p, q]
     * @return: boolean
     * @Author: Yichao Chen
     * @Date: 18-11-1
     * @Time: 下午5:09
     **/
    public boolean isEqual2(TreeNode p, TreeNode q) {
        if (p == null && q == null) return true;
        if ((p != null && q != null && p.val != q.val) || (p == null && q != null) || (p != null && q == null)) {
            return false;
        }
        boolean result;
        if (p.left != null) {
            result = isEqual2(p.left, q.left);
            if (!result)
                return false;
        }
        if (p.left == null && q.left != null) return false;
        if (p.right != null) {
            result = isEqual2(p.right, q.right);
            if (!result)
                return false;
        }
        return true;
    }

    /**
     * @Description: 牛逼，运用Stack，秒啊
     * @Param: [p, q]
     * @return: boolean
     * @Author: Yichao Chen
     * @Date: 18-11-1
     * @Time: 下午5:12
     **/
    public boolean isEqual3(TreeNode p, TreeNode q) {
        Stack<TreeNode> stack_p = new Stack<>();
        Stack<TreeNode> stack_q = new Stack<>();
        if (p != null) stack_p.push(p);
        if (q != null) stack_q.push(q);
        while (!stack_p.isEmpty() && !stack_q.isEmpty()) {
            TreeNode pn = stack_p.pop();
            TreeNode qn = stack_q.pop();
            if (pn.val != qn.val) return false;
            if (pn.right != null) stack_p.push(pn.right) ;
            if (qn.right != null) stack_q.push(qn.right) ;
            if (stack_p.size() != stack_q.size()) return false ;
            if (pn.left != null) stack_p.push(pn.left) ;
            if (qn.left != null) stack_q.push(qn.left) ;
            if (stack_p.size() != stack_q.size()) return false ;
        }
        return stack_p.size()==stack_q.size();
    }

    public static void main(String[] ar) {
        SameTree sameTree = new SameTree();
        TreeNode p, q;
        TreeNode p1, p2, p3, p4;
        TreeNode q1, q2, q3, q4;
        p = new TreeNode(1);
        q = new TreeNode(1);
        p1 = new TreeNode(2);
        p2 = new TreeNode(3);
        p3 = new TreeNode(4);
        p4 = new TreeNode(5);
        q1 = new TreeNode(2);
        q2 = new TreeNode(3);
        q3 = new TreeNode(4);
        q4 = new TreeNode(5);
        p.left = p1;
        p.right = p2;
        p2.left = p3;
        p2.right = p4;
        q.left = q1;
        q.right = q2;
        q2.left = q3;
        q2.right = q4;
        boolean result = sameTree.isSameTree(p, q);
        System.out.println(result);
    }
}
