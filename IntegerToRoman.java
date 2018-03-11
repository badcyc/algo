package dataStructure;
/*
* Given an integer, convert it to a roman numeral.
Input is guaranteed to be within the range from 1 to 3999.*/


public class IntegerToRoman {
    public static String intToRoman(int num){
        if (num<1||num>3999)return "";
        StringBuffer stringBuffer=new StringBuffer();
        String[] roman={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int[] value={1000,900,500,400,100,90,50,40,10,9,5,4,1};
        int i=0;
        while (num>0){
            while (num>=value[i]){
                num-=value[i];
                stringBuffer.append(roman[i]);
            }
            i++;
        }
        return stringBuffer.toString();
    }
    public static void main(String[] args){
        int a=2989;
        String result=intToRoman(a);
        System.out.print(result);
    }
}
