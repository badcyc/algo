package dataStructure;

/*

* Time complexity:O(log 10 n)
* space O(1)
*
*
* */

public class PalindromeNumber {
    public static boolean isPalindrome(int x){
        if (x<0||(x%10==0&&x!=0))return false;
        int revertNum=0;
        while (x>revertNum){
            revertNum=revertNum*10+x%10;
            x=x/10;
        }
        return x==revertNum||x==revertNum/10;
    }

    public static void main(String[] args){
        int a=121;
        System.out.print(isPalindrome(a));
    }
}
