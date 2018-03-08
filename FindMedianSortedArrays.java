package AlgorithmOfLeetcode;


/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
 */

/*
To solve this problem, we need to understand "What is the use of median". In statistics, the median is used for:

Dividing a set into two equal length subsets, that one subset is always greater than the other.

If we understand the use of median for dividing, we are very close to the answer.

First let's cut \text{A}A into two parts at a random position ii:

          left_A             |        right_A
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
Since \text{A}A has mm elements, so there are m+1m+1 kinds of cutting (i = 0 \sim mi=0∼m).

And we know:

\text{len}(\text{left\_A}) = i, \text{len}(\text{right\_A}) = m - ilen(left_A)=i,len(right_A)=m−i.

Note: when i = 0i=0, \text{left\_A}left_A is empty, and when i = mi=m, \text{right\_A}right_A is empty.

With the same way, cut \text{B}B into two parts at a random position jj:

          left_B             |        right_B
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
Put \text{left\_A}left_A and \text{left\_B}left_B into one set, and put \text{right\_A}right_A and \text{right\_B}right_B into another set. Let's name them \text{left\_part}left_part and \text{right\_part}right_part:

          left_part          |        right_part
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
 */
public class FindMedianSortedArrays {
    private static double findMedianSortedArrays( int[] nums1, int[] nums2){
        int m=nums1.length;
        int n=nums2.length;
        if (m>n){
            int[] temp=nums1;nums1=nums2;nums2=temp;
            int tmp=m;m=n;n=tmp;
        }
        int iMin=0,iMax=m,halfLen=(m+n+1)/2;
        while (iMin<=iMax){
            int i=(iMin+iMax)/2,j=halfLen-i;
            if (i<iMax&&nums2[j-1]>nums1[i]){
                iMin=iMin+1;
            }
            else if (i>iMin&&nums1[i-1]>nums2[j]){
                iMax=iMax-1;
            }
            else {
                int maxLeft=0;
                if (i==0) maxLeft=nums2[j-1];
                else if (j==0) maxLeft=nums1[i-1];
                else maxLeft=Math.max(nums1[i-1],nums2[j-1]);
                if ((m+n)%2==1) return maxLeft;
                int minRight=0;
                if (i == m) { minRight = nums2[j]; }
                else if (j == n) { minRight = nums1[i]; }
                else { minRight = Math.min(nums2[j], nums1[i]); }

                return (maxLeft + minRight) / 2.0;
            }
        }
        return 0.0;
    }
    public static void main(String... args){
        int[] num1={1,3,4,5,7,12};
        int[] num2={2,5,6,8,10,11};
        double result=findMedianSortedArrays(num1,num2);
        System.out.println(result);
    }
}
