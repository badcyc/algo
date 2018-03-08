package dataStructure;

public class ReverseInteger {
    public static Integer reverseInteger(final Integer integer){
        Integer i=integer;
        Integer result=0;
        while (i!=0){
            Integer tail=i%10;
            Integer newResult=result*10+tail;
            result=newResult;
            i=i/10;
        }
        return result;
    }
    public static void main(String[] args){
        Integer i=12345;
        Integer result=reverseInteger(12345);
        System.out.print(result);
    }
}
