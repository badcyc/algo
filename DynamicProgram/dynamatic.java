package dataStructure.DynamicProgram;

import java.util.HashMap;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-10-29 16:44
 **/
public class dynamatic {
    /**
     * @Description: 递归 自顶向下
     * @Param: [p, r]　p 代表收益，r 代表剩下的长度
     * @return: int　返回最大收益
     * @Author: Yichao Chen
     * @Date: 18-10-29
     * @Time: 下午4:47
     **/
    public static int maxValue(int[] p, int r) {
        if (r == 0) return 0;
        int max = -1;
        for (int i = 1; i <= r; i++) {
            max = Math.max(max, p[i] + maxValue(p, r - i));
            System.out.println('i' + Integer.toString(i));
            System.out.println(max);
        }
        return max;
    }

    /////////////////////////////////////////////////////////////////////////////////
    /**
     * @Description: 自顶向下　带备忘录
     * @Param: [p, r]参数返回值如上
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-29
     * @Time: 下午5:10
     */
    public static HashMap<Integer, Integer> maxValue = new HashMap<Integer, Integer>();

    public static int topDownWithMem(int[] p, int r) {
        if (r == 0) return 0;
        int max = -1;
        for (int i = 1; i <= r; i++) {
            if (maxValue.containsKey(r - i)) {
                max = Math.max(max, p[i] + maxValue.get(r - i));
            } else {
                max = Math.max(max, p[i] + topDownWithMem(p, r - i));
            }
        }
        maxValue.put(r, max);
        return max;
    }

    /**
     * @Description: 带备忘录的自底向上
     * @Param: [p, r]
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 上午10:44
     **/
    public static int BottomUpWithMem(int[] p, int r) {
        HashMap<Integer, Integer> rMax = new HashMap<>();
        int max = -1;
        rMax.put(0, 0);
        for (int j = 1; j <= r; j++) {
            for (int k = 1; k <= j; k++) {
                max = Math.max(max, p[k] + rMax.get(j - k));
            }
            rMax.put(j, max);
        }
        return max;
    }

    /**
     * @Description: 钢管切割，每次有费用
     * @Param:
     * @return:
     * @Author: Yichao Chen
     * @Date: 18-10-29
     * @Time: 下午9:06
     **/
    static HashMap<Integer, Integer> rMax = new HashMap<>();

    public static int BottomUpWithMemAndC(int[] p, int r, int c) {
//        HashMap<Integer, Integer> rMax = new HashMap<>();
        int max = -1;
        rMax.put(0, 0);
        for (int j = 1; j <= r; j++) {
            for (int k = 1; k < j; k++) {
                max = Math.max(max, p[k] + rMax.get(j - k) - c);
            }
            max = Math.max(max, p[j]);
            rMax.put(j, max);
        }
        return max;
    }

//    public static int

    public static int stringSplit(String content, int[] m, int first, int end) {
        int min = Integer.MIN_VALUE;
        if (end - first == 1) {
            return m[end] - m[first];
        }
        for (int i = 0; i < m.length; ++i) {
            min = Math.min(stringSplit(content, m, first, i) + stringSplit(content, m, i, end), min);
        }
        return min;
    }

    public static void main(String[] args) {
        int[] p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
//        int maxVaulue = maxValue(p, 4);
//        int maxVaulue = topDownWithMem(p, 4);
//        int maxVaulue = BottomUpWithMemAndC(p, 5, 1);
//        for (int i = 0; i <= 5; i++) {
//            if (rMax.containsKey(i)) {
//                System.out.println(i + " maxValue: " + rMax.get(i));
//            }
//        }
//        System.out.print(maxVaulue);
        String content="";
        int[] m={2,8,10};
        int min=stringSplit(content,m,0,20);
    }
}
