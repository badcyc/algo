package AlgorithmOfLeetcode;

/**
 * Given a string, find the length of the longest substring without repeating characters.
 Examples:
 Given "abcabcbb", the answer is "abc", which the length is 3.
 Given "bbbbb", the answer is "b", with the length of 1.
 Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */

public class LongSubstring {
    public static int lengthOfLongestSubstring(String s) {
        int n = s.length(), ans = 0;
        int[] index = new int[128];
        for (int j = 0, i = 0; j < n; j++) {
            i = Math.max(index[s.charAt(j)], i);
            ans=Math.max(ans,j-i+1);
            index[s.charAt(j)]=j+1;
        }
        return ans;
    }
    public static void main(String[] s){
        String a="abcdeafgh";
        System.out.println(lengthOfLongestSubstring(a));
        int [] array=new int[128];
        for (int i=0;i<128;i++){
            array[i]=i;
        }
        System.out.println(array[0]+" "+array['a']+" "+array[2]);
    }
}
