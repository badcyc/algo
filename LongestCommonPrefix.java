package dataStructure;
/*
* code of origin
* */
public class LongestCommonPrefix {
    public static String longestCommonPrefix(String[] strings){
        StringBuffer result=new StringBuffer();
        int length=strings.length;
        for (int i=0;i<strings[0].length();i++){
            int j=1;
            char flag=strings[0].charAt(i);
            while (j<length&&i<strings[j].length()&&flag==strings[j].charAt(i)){
                j++;
            }
            if (j==length){
                result.append(flag);
            }else {
                break;
            }
        }
        return result.toString();
    }

/*-----------------------------Divide and conquer---------------------
Time complexity : O(S)O(S)
Space complexity : O(m*log(n))O(m∗log(n))

 */

    public static String longestCommonPrefix_1(String[] strings){
        if (strings==null||strings.length==0)return "";
        return longestCommonPrefix_1(strings,0,strings.length-1);
    }
    public static String longestCommonPrefix_1(String[] strings,int l,int r){
        if (r==l){
            return strings[l];
        }else {
            int mid=(l+r)/2;
            String lstr=longestCommonPrefix_1(strings,l,mid);
            String rstr=longestCommonPrefix_1(strings,mid+1,r);
            return commonPrefix(lstr,rstr);
        }
    }
    static String commonPrefix(String left,String right){
        int min = Math.min(left.length(), right.length());
        for (int i = 0; i < min; i++) {
            if ( left.charAt(i) != right.charAt(i) )
                return left.substring(0, i);
        }
        return left.substring(0, min);
    }
// ----------------------------------------------------------------------

//    ---------------------Binary search--------------------------------------------

    /*
    Time complexity : O(S*log(n))O(S∗log(n))
    Space complexity : O(1)O(1).
     */
    public static String longestCommonPrefix_2(String[] strs) {
        if (strs == null || strs.length == 0)
            return "";
        int minLen = Integer.MAX_VALUE;
        for (String str : strs)
            minLen = Math.min(minLen, str.length());
        int low = 1;
        int high = minLen;
        while (low <= high) {
            int middle = (low + high) / 2;
            if (isCommonPrefix(strs, middle))
                low = middle + 1;
            else
                high = middle - 1;
        }
        return strs[0].substring(0, (low + high) / 2);
    }

    private static boolean isCommonPrefix(String[] strs, int len){
        String str1 = strs[0].substring(0,len);
        for (int i = 1; i < strs.length; i++)
            if (!strs[i].startsWith(str1))
                return false;
        return true;
    }
    //----------------------------------------------------
  public static void main(String[] args){
        String[] test={"abbccccc","abcd",""};
        String result=longestCommonPrefix(test);
        System.out.print(result);
        result=longestCommonPrefix_1(test);
        System.out.print(result);
      result=longestCommonPrefix_2(test);
      System.out.print(result);

  }
}
