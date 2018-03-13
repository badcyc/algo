package dataStructure;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class LetterCombOfPhoneNum {


    /*
    *
    * peek() This method returns the head of this list, or null if this list is empty
    * remove() This method remove the head of this list,
    * LinkedList 基于链式
    *
    * */
    public static List<String> letterCombinations(String digits){
        LinkedList<String> ans = new LinkedList<String>();
        if(digits.isEmpty()) return ans;
        String[] mapping = new String[] {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        ans.add("");
        for(int i =0; i<digits.length();i++){
            int x = Character.getNumericValue(digits.charAt(i));
            while(ans.peek().length()==i){
                String t = ans.remove();
                for(char s : mapping[x].toCharArray())
                    ans.add(t+s);
            }
        }
        return ans;
    }
    public static void main(String[] args){
        String digits="345";
        List<String> result=letterCombinations(digits);
        for (String a:result){
            System.out.println(a);
        }
    }
}
