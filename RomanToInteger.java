package dataStructure;


// String[] roman={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
//    int[] value={1000,900,500, 400,100, 90,  50, 40,  10,  9,   5,   4,   1};
public class RomanToInteger {
    public static int romanToInteger(String roman){
        int length=roman.length();
        int i=0;int result=0;
        while (i<length){
            switch (roman.charAt(i)){
                case 'M':
                    result+=1000;
                    break;
                case 'C':
                    if (i+1<length&&roman.charAt(i+1)=='M'){
                        result+=900;
                        i++;
                    }else if (i+1<length&&roman.charAt(i+1)=='D'){
                        result+=400;
                        i++;
                    }else {
                        result+=100;
                    }
                    break;
                case 'D':
                    result+=500;
                    break;
                case 'X':
                    if (i+1<length&&roman.charAt(i+1)=='C'){
                        result+=90;
                        i++;
                    }else if (i+1<length&&roman.charAt(i+1)=='L'){
                        result+=40;
                        i++;
                    }else {
                        result+=10;
                    }
                    break;
                case 'L':
                    result+=50;
                    break;
                case 'I':
                    if (i+1<length&&roman.charAt(i+1)=='X'){
                        result+=9;
                        i++;
                    }else if (i+1<length&&roman.charAt(i+1)=='V'){
                        result+=4;
                        i++;
                    }else {
                        result+=1;
                    }
                    break;
                case 'V':
                    result+=5;
                    break;
                    default:
                        return 0;
            }
            i++;
        }
        return result;
    }
    public static void main(String[]args){
        String test="MMCMLXXXIX";
        int result=romanToInteger(test);
        System.out.print(result);
    }
}
