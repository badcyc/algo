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
        Stack<Character> characters = new Stack<>();
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                characters.push('(');
            } else if (!characters.empty() && characters.peek() == '(') {
                characters.pop();
            } else return false;
        }
        return characters.empty();
    }

    public static int longestValidParentheses(String s) {
        int max = 0;
        for (int i = 0; i < s.length(); i++) {
            for (int j = i + 2; j <= s.length(); j += 2) {
                if (isValid(s.substring(i, j))) {
                    max = Math.max(max, j - i);
                }
            }
        }
        return max;
    }

    /**
     * @Description: 动态规划解决 牛逼的解法
     * @Param: [args]
     * @return: void
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 上午12:22
     **/
    public static int DP(String s) {
        int maxans = 0;
        int dp[] = new int[s.length()];
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) == ')') {
                if (s.charAt(i - 1) == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s.charAt(i - dp[i - 1] - 1) == '(') {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                maxans = Math.max(maxans, dp[i]);
            }
        }
        return maxans;
    }

    public static void main(String[] args) {
        String s = "()(()";
        int max = longestValidParentheses(s);
        System.out.println(max);
    }
}
