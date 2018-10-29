package dataStructure.DynamicProgram;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-10-29 23:29
 **/

import java.util.Stack;

/**
 * 121111222111121
 * 121111222111121
 * 思路将字符串翻转后进行比较
 */
public class LongestValidParentheses {
    public static boolean isValid(String s) {
//        String reverse=new StringBuilder(s).reverse().toString();
//        if (s.equals(reverse)){
//            return true;
//        }
//        return false;
        Stack<Character> characters = new Stack<>();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                characters.push('(');
            } else if (!characters.empty() && characters.peek() == '(') {
                characters.pop();
            } else return false;
        }
        return true;
    }

    public static int longestValidParentheses(String s) {
        int max = -1;
        for (int i = 0; i < s.length(); i++) {
            for (int j = i + 2; j <= s.length(); j += 2) {
                if (isValid(s.substring(i, j))) {
                    max = Math.max(max, j - i);
                }
            }
        }
        return max;
    }

    public static void main(String[] args) {
        String s = "))((())";
        int max = longestValidParentheses(s);
        System.out.println(max);
    }
}
