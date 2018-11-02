package dataStructure.leetcode.HashTable;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @program: algo
 * @description: 4 sum
 * @author: Yichao Chen
 * @create: 2018-11-02 18:37
 **/

//Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
//
//        A solution set is:
//        [
//        [-1,  0, 0, 1],
//        [-2, -1, 1, 2],
//        [-2,  0, 0, 2]
//        ]
public class FourSum {
    /**
     * @Description: 时间复杂度过高，n(n-1)(n-2) =< Ｏ <= n(n-1)(n-2)   Ｏ(n^3)+Ｏ(n*log n)
     * @Param: [nums, target]
     * @return: java.util.List<java.util.List               <               java.lang.Integer>>
     * @Author: Yichao Chen
     * @Date: 18-11-2
     * @Time: 下午7:14
     **/
    public static List<List<Integer>> fourSum(int[] nums, int target) {
        List<List<Integer>> integerlists = new ArrayList<>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] >= 0 && nums[i] > target) break;
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[j] >= 0 && nums[i] + nums[j] > target) break;
                for (int k = j + 1; k < nums.length; k++) {
                    if (nums[k] >= 0 && nums[i] + nums[j] + nums[k] > target) break;
                    for (int l = k + 1; l < nums.length; l++) {
                        int total = nums[i] + nums[j] + nums[k] + nums[l];
                        if (total == target) {
                            List<Integer> integers = new ArrayList<>();
                            integers.add(nums[i]);
                            integers.add(nums[j]);
                            integers.add(nums[k]);
                            integers.add(nums[l]);
                            if (!integerlists.contains(integers))
                                integerlists.add(integers);
                        } else if (total > target) {
                            break;
                        }
                    }
                }
            }
        }
        return integerlists;
    }

    /**
     * @Description: 题目分解　其中对二个数时　进行二分法　每个问题都能避免大部分的计算
     * @Param: [nums, target]
     * @return: void
     * @Author: Yichao Chen
     * @Date: 18-11-2
     * @Time: 下午7:15
     **/
    public static List<List<Integer>> fourSums(int[] nums, int target) {
        ArrayList<List<Integer>> res = new ArrayList<List<Integer>>();
        int len = nums.length;
        if (nums == null || len < 4)
            return res;

        Arrays.sort(nums);

        int max = nums[len - 1];
        if (4 * nums[0] > target || 4 * max < target)
            return res;

        int i, z;
        for (i = 0; i < len; i++) {
            z = nums[i];
            if (i > 0 && z == nums[i - 1])// avoid duplicate
                continue;
            if (z + 3 * max < target) // z is too small
                continue;
            if (4 * z > target) // z is too large
                break;
            if (4 * z == target) { // z is the boundary
                if (i + 3 < len && nums[i + 3] == z)
                    res.add(Arrays.asList(z, z, z, z));
                break;
            }

            threeSumForFourSum(nums, target - z, i + 1, len - 1, res, z);
        }

        return res;
    }

    public static void threeSumForFourSum(int[] nums, int target, int low, int high, ArrayList<List<Integer>> fourSumList,
                                          int z1) {
        if (low + 1 >= high) return;
        int max = nums[high];
        if (3 * nums[low] > target || 3 * max < target) return;
        int i, z;
        for (i = low; i < high - 1; i++) {
            z = nums[i];
            if (i > low && z == nums[i - 1]) continue;
            if (z + 2 * max < target) continue;
            if (3 * z > target) break;
            if (3 * z == target) {
                if (i + 1 < high && nums[i + 2] == z)
                    fourSumList.add(Arrays.asList(z1, z, z, z));
                break;
            }
            twoSumForFourSum(nums, target - z, i + 1, high, fourSumList, z1, z);
        }
    }

    public static void twoSumForFourSum(int[] nums, int target, int low, int high, ArrayList<List<Integer>> fourSumList
            , int z1, int z2) {
        if (low >= high)
            return;
        if (nums[low] * 2 > target || nums[high] * 2 < target) return;
        int i = low, j = high, mid = i + (j - i) / 2, sum, x;
        while (i < j) {
            sum = nums[i] + nums[j];
            if (sum == target) {
                fourSumList.add(Arrays.asList(z1, z2, nums[i], nums[j]));
            }
            x = nums[i];
            while (++i < j && x == nums[i])
                ;
            x = nums[j];
            while (--j > i && nums[j] == x)
                ;
            if (sum < target) i++;
            if (sum > target) j--;
        }
        return;
    }

    public static void main(String[] args) {
        int[] nums = {1, 0, -1, 0, -2, 2};
        List<List<Integer>> lists = new ArrayList<>();
        lists = fourSum(nums, 0);
        for (List<Integer> list : lists
                ) {
            for (Integer i : list
                    ) {
                System.out.print(i + " ");
            }
            System.out.println();
        }
    }
}
