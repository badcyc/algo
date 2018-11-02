package dataStructure.datastructure.spider;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Main {
    public static void main(String[] a){
//        Jsoup jsoup=new Jsoup();
//        jsoup.startSpider();
        Date date=new Date();
        SimpleDateFormat simpleDateFormat=new SimpleDateFormat("yyyy-MM-dd");
        System.out.print(simpleDateFormat.format(date));

    }
}
