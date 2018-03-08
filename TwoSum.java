package AlgorithmOfLeetcode;


import java.util.HashMap;
import java.util.Map;

public class TwoSum {
    public static int[] twoSum(int[] array,int target){
        Map<Integer,Integer> integer=new HashMap<>();
        for (int i=0;i<array.length;i++){
            integer.put(array[i],i);
        }
        for (int i=0;i<array.length;i++){
            Integer complement=target-array[i];
            if (integer.containsKey(complement)){
                return new int[]{integer.get(complement),i};
            }
        }
        throw  new IllegalArgumentException("No two sum solution");
    }
    public static void main(String[]args){
        int[] array={1,2,3,4,5,6,7,8,9};
        int[]solution=twoSum(array,12);
        System.out.print(solution[0]);
        System.out.print(solution[1]);
    }
}
