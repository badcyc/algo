package dataStructure.BinarySearch;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-10-30 00:43
 **/
public class SearchInsert {
    public static int searchInsert(int[] nums, int target) {
        int i;
        if (nums[0]>=target)return 0;
        for (i = 1; i < nums.length; i++) {
            if (nums[i] == target) return i;
            if (nums[i] > target && i >= 1 && nums[i - 1] < target) {
                return i;
            }
        }
        return i;
    }

    public static void main(String[] a) {
        int[] nums = {1, 3, 4, 5, 6};
        int re = searchInsert(nums, 2);
        System.out.println(re);
    }
}
