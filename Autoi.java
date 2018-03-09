package dataStructure;

public class Autoi {
    public static int autoi(String str){
        if (str.isEmpty())return 0;
        int sign=1,base=0,i=0;
        while (str.charAt(i)==' '){
            i++;
        }

        //String str=str1.trim();
        if (str.charAt(i)=='-'||str.charAt(i)=='+')
            sign=str.charAt(i++)=='-'?-1:1;
        while (i<str.length()&&str.charAt(i)>='0'&&str.charAt(i)<='9'){
            if (base>Integer.MAX_VALUE/10||(base==Integer.MAX_VALUE/10&&str.charAt(i)-'0'>7)){
                return sign==1?Integer.MAX_VALUE:Integer.MIN_VALUE;
            }
            base=10*base+(str.charAt(i++)-'0');
        }
        return base*sign;
    }
    public static void main(String[]args){
        String str_mock="                        112233444444444";
        Integer result=autoi(str_mock);
        System.out.print(result);
    }
}
