package dataStructure.leetcode.Stack;

import java.util.*;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-11-11 20:34
 **/
/*
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
 */

//  Definition for a binary tree node.

public class BinaryTreeZigzagLevelOrderTraversal {
    static class TreeNode {
        int val;
        TreeNode left = null;
        TreeNode right = null;

        TreeNode(int x) {
            val = x;
        }
    }

    public static List<Integer> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> lists = new ArrayList<>();
        List<Integer> integers = new ArrayList<>();
        Queue<TreeNode> nodeQueue = new LinkedList<>();
        nodeQueue.offer(root);
        Map<Integer, Integer> map = new HashMap<>();
        int j = 0;
        j++;
        map.put(j, 1);
        while (!nodeQueue.isEmpty()) {
            TreeNode node = nodeQueue.poll();
            if (node != null) {
                if (map.containsKey(j) && map.get(j) == 0) {
                    j--;
                }
                map.put(j, map.get(j) - 1);
                integers.add(node.val);
            }
            j++;
            if (!map.containsKey(j))
                map.put(j, 0);
            if (j % 2 == 1) {
                if (node.left == null && node.right == null) {
                    j--;
                    continue;
                }
                if (node.left != null) {
                    nodeQueue.offer(node.left);
                    map.put(j, map.get(j) + 1);
                }
                if (node.right != null) {
                    nodeQueue.offer(node.right);
                    map.put(j, map.get(j) + 1);
                }
            } else {
                if (node.right != null) {
                    nodeQueue.offer(node.right);
                    map.put(j, map.get(j) + 1);
                }
                if (node.left != null) {
                    nodeQueue.offer(node.left);
                    map.put(j, map.get(j) + 1);
                }
            }
//            j++;
        }
        return integers;
    }


    public static void main(String[] args) {
        TreeNode root = new TreeNode(1);
        TreeNode node = new TreeNode(2);
        TreeNode node1 = new TreeNode(3);
        TreeNode node2 = new TreeNode(4);
        TreeNode node3 = new TreeNode(5);
        TreeNode node4 = new TreeNode(6);
        TreeNode node5 = new TreeNode(7);
        root.left = node;
        root.right = node1;
        node.left = node2;
        node.right = node3;
        node1.left=node4;
        node1.right=node5;
        List<Integer> integerList = BinaryTreeZigzagLevelOrderTraversal.zigzagLevelOrder(root);
        integerList.forEach((i) -> {
            System.out.println(i);
        });
    }
}
