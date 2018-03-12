package dataStructure;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class threeSum {

//    -----------------------mine is error-----------------------------
    public static List<List<Integer>> threeSum(int []nums){
        List<List<Integer>> lists=new ArrayList<>();
        List<List<Integer>> list=new ArrayList<>();
        List<Integer> integers=new ArrayList<>();
        for (int i=0;i<nums.length;i++){
            list=twoSum(removeElem(nums,i),0-nums[i]);
            if (list==null) continue;
            for (int j=0;j<list.size();j++){
                    integers.addAll(list.get(j));
                    integers.add(nums[i]);
                    if (!lists.contains(integers))
                    lists.add(integers);
            }
        }
        return lists;
    }
    public static List<List<Integer>> twoSum(int[]sums,int target){
        int length=sums.length;
        List<List<Integer>> lists=new ArrayList<>();
        for (int i=0;i<length;i++){
            for (int j=i+1;j<length;j++){
                if (sums[i]==target-sums[j]){
                    List<Integer> integers=new ArrayList<>(2);
                    integers.add(sums[i]);
                    integers.add(sums[j]);
                    lists.add(integers);
                }
            }
        }
        return lists;
    }
    public static int[] removeElem(int[] sums,int i){
        int[] result=sums;int j;
        if (i>=sums.length)return sums;
        for (j=i;j<sums.length-1;j++){
            result[j]=result[j+1];
        }
        result[sums.length-1]='\0';
        return result;
    }
// --------------------------------------------------------------------------------------
   public static List<List<Integer>> threeSum_1(int[] num) {
        Arrays.sort(num);
        List<List<Integer>> res = new LinkedList<>();
        for (int i = 0; i < num.length-2; i++) {
            if (i == 0 || (i > 0 && num[i] != num[i-1])) {
                int lo = i+1, hi = num.length-1, sum = 0 - num[i];
                while (lo < hi) {
                    if (num[lo] + num[hi] == sum) {
                        res.add(Arrays.asList(num[i], num[lo], num[hi]));
                        while (lo < hi && num[lo] == num[lo+1]) lo++;
                        while (lo < hi && num[hi] == num[hi-1]) hi--;
                        lo++; hi--;
                    } else if (num[lo] + num[hi] < sum) {
                        // improve: skip duplicates
                        while (lo < hi && num[lo] == num[lo+1]) lo++;
                        lo++;
                    } else {
                        // improve: skip duplicates
                        while (lo < hi && num[hi] == num[hi-1]) hi--;
                        hi--;
                    }
                }
            }
        }
        return res;
    }
    public static void main(String[] args){
        int[] nums={-1,0,1,2,-1,-4};
        List<List<Integer>> result=threeSum_1(nums);
        for (int i=0;i<result.size();i++){
            List<Integer> integers=result.get(i);
            for (int j=0;j<integers.size();j++){
                System.out.print(integers.get(j)+" ");
            }
            System.out.println();
        }
    }
}
