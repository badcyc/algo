package dataStructure.leetcode.DynamicProgram;

import java.util.ArrayList;
import java.util.List;

/**
 * @program: algo
 * @description: Unique Binary Search Trees II
 * @author: Yichao Chen
 * @create: 2018-11-06 00:15
 **/

/**
 * Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.
 *
 *
 * Example:
 *
 * Input: 3
 * Output:
 * [
 *   [1,null,3,2],
 *   [3,2,null,1],
 *   [3,1,null,null,2],
 *   [2,1,3],
 *   [1,null,2,null,3]
 * ]
 * Explanation:
 * The above output corresponds to the 5 unique BST's shown below:
 *
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int x) {
        val = x;
    }
}

public class UniqueBinarySearchTrees {
    public List<TreeNode> generateTrees(int n) {
        return g(1, n);
    }

    /**
     * @Description: 动态规划，未备忘递归
     * @Param: [start, end]
     * @return: java.util.List<dataStructure.leetcode.DynamicProgram.TreeNode>
     * @Author: Yichao Chen
     * @Date: 18-11-6
     * @Time: 上午12:58
     **/
    private List<TreeNode> g(int start, int end) {
        List<TreeNode> rootList = new ArrayList<>();
        if (start > end) return rootList;
        if (start == end) {
            rootList.add(new TreeNode(start));
        }
        for (int i = start; i <= end; ++i) {
            List<TreeNode> leftList = g(start, i - 1);
            List<TreeNode> rightList = g(i + 1, end);
            for (int j = 0; j < (leftList.size() == 0 ? 1 : leftList.size()); ++j) {
                for (int k = 0; k < (rightList.size() == 0 ? 1 : rightList.size()); ++k) {
                    TreeNode root = new TreeNode(i);
                    if (leftList.size() != 0)
                        root.left = leftList.get(j);
                    if (rightList.size() != 0)
                        root.right = rightList.get(k);
                    if (leftList.size() != 0 || rightList.size() != 0)
                        rootList.add(root);
                }
            }
        }
        return rootList;
    }

    public static void main(String[] args) {
        UniqueBinarySearchTrees trees = new UniqueBinarySearchTrees();
        int n = trees.generateTrees(2).size();
        System.out.println(n);
    }
}

