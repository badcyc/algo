package dataStructure;
/*
*
*
* Given an array S of n integers,
* find three integers in S such that the sum is closest to a given number, target.
* Return the sum of the three integers.
* You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*
*
* */
import java.util.Arrays;

public class threeSumClosest {
    public static int threeSumCloest(int[] nums,int target){
        int result=Integer.MAX_VALUE;int finalResult=0;
        Arrays.sort(nums);
        for (int i=0;i<nums.length-2;i++){
            int flag_1=0,flag_2=0;
            int lo=i+1,ro=nums.length-1,sum=target-nums[i];
            while (lo<ro){
                if (nums[lo]+nums[ro]==sum)
                {
                    return nums[lo]+nums[ro]+nums[i];
                }

                else if (nums[lo]+nums[ro]>sum){
                    flag_2=1;
                    while (lo<ro&&nums[ro]==nums[ro-1]) ro--;
                    if(Math.abs(nums[lo]+nums[ro]-sum)<result){
                        result=Math.abs(nums[lo]+nums[ro]-sum);
                        finalResult=nums[lo]+nums[ro]+nums[i];
                    }
                    if (flag_1==1){
                        break;
                    }
                    ro--;
                }else if (nums[lo]+nums[ro]<sum){
                    flag_1=1;
                    while (lo<ro&&nums[lo]==nums[lo+1]) lo++;
                    if(Math.abs(nums[lo]+nums[ro]-sum)<result){
                        result=Math.abs(nums[lo]+nums[ro]-sum);
                        finalResult=nums[lo]+nums[ro]+nums[i];
                    }
                    if (flag_2==1)
                        break;
                    lo++;
                }
            }
        }
        return finalResult;
    }
    public static void main(String[] args){
        int[] test={-1,2,1,-4,3};
        int result=threeSumCloest(test,3);
        System.out.println(result);
    }
}
