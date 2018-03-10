package dataStructure;

public class ContainerWithMostWater {

    /*
    * solution 1
    * time : o(n^2)
    * space: o(1)
    * */
    public static int maxArea(int[] height){
        int maxArea=0;
        for (int i=0;i<height.length;i++){
            for (int j=i+1;j<height.length;i++){
                maxArea=Math.max(maxArea,Math.min(height[i],height[j])*(j-i));
            }
        }
        return maxArea;
    }

    /*
    * solution 2
    * time :o(n)
    * space:o(1)
    *
    * How this approach works?

Initially we consider the area constituting the exterior most lines.
Now, to maximize the area, we need to consider the area between the lines of larger lengths.
If we try to move the pointer at the longer line inwards, we won't gain any increase in area,
since it is limited by the shorter line.
 But moving the shorter line's pointer could turn out to be beneficial,
 as per the same argument, despite the reduction in the width.
 This is done since a relatively longer line obtained by moving the shorter
line's pointer might overcome the reduction in area caused by the width reduction.
    * */
    public static int maxArea_2(int[] height){
        int maxArea=0,l=0,r=height.length-1;
        while (l<r){
            maxArea=Math.max(maxArea,Math.min(height[l],height[r])*(r-l));
            if (height[l]<height[r])
                l++;
            else r--;

        }
        return maxArea;
    }
    public static void main(String[] args){

    }
}
