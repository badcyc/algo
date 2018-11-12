package dataStructure.leetcode.string;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-11-06 23:13
 **/
public class CountAndSay {
    public String countAndSay(int n) {
        return count(n - 1);
    }

    public String count(int n) {
        String ret = "1";
        int i = 0;
        while (i < n) {
            i++;
            StringBuilder stringBuilder = new StringBuilder();
            int j = 0, k = 0;
            char c = ret.charAt(j);

            while (j < ret.length()) {
                k++;
                if ((j + 1 != ret.length() && c != ret.charAt(j + 1)) || j + 1 == ret.length()) {
                    stringBuilder.append(k);
                    stringBuilder.append(c);
                    k = 0;
                    c = (j + 1 == ret.length()) ? ret.charAt(j) : ret.charAt(j + 1);
                }
                j++;
            }
            ret = stringBuilder.toString();
        }
        return ret;
    }

    public static void main(String[] args) {
        CountAndSay countAndSay = new CountAndSay();
        String ret = countAndSay.countAndSay(4);
        System.out.println(ret);
    }
}
