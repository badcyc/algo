package dataStructure.algolabs.DivideAndConquer;

import java.util.Arrays;

/**
 * @program: algo
 * @description: 大整数运算
 * @author: Yichao Chen
 * @create: 2018-10-30 20:18
 **/
public class BigUtil {

    class NumDivider {
        char[] a;
        char[] b;
        int aLength;
        int bLength;

        public NumDivider(char[] input) {
            aLength = input.length / 2;
            bLength = input.length - aLength;
            a = new char[aLength];
            b = new char[bLength];
            for (int i = 0; i < aLength; i++) {
                a[i] = input[i];
            }
            for (int i = 0; i < bLength; i++) {
                b[i] = input[aLength + i];
            }
        }
    }

    private NumDivider divider(char[] input) {
        return new NumDivider(input);
    }

    /**
     * @Description: 前面补0;
     * @Param: [num, length]
     * @return: char[]
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午8:45
     **/
    public static char[] format(char[] num, int length) {
        if (num.length >= length) {
            return num;
        }
        char[] result = new char[length];
        for (int i = 0; i < length - num.length; i++) {
            result[i] = '0';
        }
        for (int i = 0; i < num.length; i++) {
            result[length - num.length + i] = num[i];
        }
        return result;
    }

    /**
     * @Description: 两个数组的长度统一
     * @Param: [num1, num2]
     * @return: char[]
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午8:48
     **/
    private int lengthOfNums(char[] num1, char[] num2) {
        return num1.length >= num2.length ? num1.length : num2.length;
    }

    /**
     * @Description: 大数相加
     * @Param: [num1, num2]　位数加１
     * @return: char[]
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午8:59
     **/
    public char[] add(char[] num1, char[] num2) {
        int carry = 0;//进位
        int length = lengthOfNums(num1, num2);
        num1 = format(num1, length);
        num2 = format(num2, length);
        char[] result = new char[length + 1];
        for (int i = length - 1; i >= 0; i--) {
            int tmp = num1[i] + num2[i] + carry - 96;
            if (tmp >= 10) {
                carry = 1;
                tmp -= 10;
            } else carry = 0;
            result[i + 1] = (char) (tmp + 48);
        }
        result[0] = (char) (carry + 48);
        return result;
    }

    /**
     * @Description: 大数相减
     * @Param: [num1, num2]
     * @return: char[]
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午9:00
     **/
    public char[] sub(char[] num1, char[] num2) {
        int len = num1.length > num2.length ? num1.length : num2.length;
        char[] num1Copy = Arrays.copyOf(format(num1, len), len);
        char[] num2Copy = Arrays.copyOf(format(num2, len), len);

        return num1;//todo
    }

    public char[] mul(char[] num1, char[] num2) {
        char[] A, B, C, D, AC, BD, A_B, D_C, A_BxC_D;
        A = new char[2];
        return A;
    }

    public static void main(String[] ars) {
        char[] chars = {'a', 'b'};
        char[] newchar = Arrays.copyOf(BigUtil.format(chars, 5), 5);
        System.out.println(chars.length);
        System.out.println(newchar);
    }

}
