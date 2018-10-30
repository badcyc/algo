package dataStructure.DivideAndConquer;


import java.util.Arrays;
import java.util.Comparator;
import java.util.Random;

/**
 * @program: algo
 * @description:　最近点对
 * @author: Yichao Chen
 * @create: 2018-10-30 15:54
 **/
class Point {
    double x;
    double y;
}

public class ClosestPair {


    class MyComprator implements Comparator {
        @Override
        public int compare(Object o1, Object o2) {
            Point a = (Point) o1;
            Point b = (Point) o2;
            return compareXY(a, b);
        }
    }

    /**
     * @Description: 求两点的距离
     * @Param: [a, b]point a;point b
     * @return: double
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午4:01
     **/
    private double distanceOfPoints(Point a, Point b) {
        return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    /**
     * @Description:自定义排序规则：依照结构体中的x成员变量升序排序
     * @Param: [a, b]
     * @return: boolean a的横坐标是否小于b的横坐标
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午4:02
     **/
    private int compareX(Point a, Point b) {
        return a.x < b.x ? 1 : -1;
    }

    /**
     * @Description:自定义排序规则：依照结构体中的y成员变量升序排序
     * @Param: [a, b]
     * @return: boolean a的纵坐标是否小于b的纵坐标
     * @Author: Yichao Chen
     * @Date: 18-10-30
     * @Time: 下午4:02
     **/
    private int compareY(Point a, Point b) {
        return a.y < b.y ? 1 : -1;
    }

    private int compareXY(Point a, Point b) {
        if (a.x != b.x) {
            return compareX(a, b);
        } else {
            return compareY(a, b);
        }
    }

    private Point[] sort(Point[] points) {
        Arrays.sort(points, new MyComprator());
        return points;
    }

    public double cloest(Point[] points) {
        Point[] pointsSorted = sort(points);
        return cloestPair(pointsSorted);
    }

    Point a, b;

    private double cloestPair(Point[] points) {
        //两点
        if (points.length == 2) {
            a = points[0];
            b = points[1];
            return distanceOfPoints(points[0], points[1]);
        }
        //三点
        if (points.length == 3) {
            double d1 = distanceOfPoints(points[0], points[1]);
            double d2 = distanceOfPoints(points[0], points[2]);
            double d3 = distanceOfPoints(points[1], points[2]);
            double d;
            d = (d = d1 > d2 ? d2 : d1) > d3 ? d3 : d;
            if (d == d1) {
                a = points[0];
                b = points[1];
                return d;
            }
            if (d == d2) {
                a = points[0];
                b = points[2];
                return d;
            }
            if (d == d3) {
                a = points[1];
                b = points[2];
            }
        }
        //多于三点 分治
        double ld;
        double rd;
        double distance;
        int lLength = (points.length - 1) / 2;
        double mid = points[lLength].x;
        Point[] lps = new Point[lLength];
        Point[] rps = new Point[points.length - lLength];
        ld = cloestPair(lps);
        rd = cloestPair(rps);
        //todo
        if (ld < rd) {
            distance = ld;
        } else {
            distance = rd;
        }
        //todo
        Point[] points3 = new Point[points.length];
        int i = lLength;
        int k = 0;
        while (i >= 0 && mid - points[i].x >= distance) {
            points3[k++] = points[i];
            i--;
        }
        i = lLength + 1;
        while (i < points.length && points[i].x - mid <= distance) {
            points3[k++] = points[i];
            i++;
        }
        Point[] points3Sorted = sort(points3);
        int j = 0, x = 0;
        for (i = 0; i < k; i++) {
            if (points3Sorted[j].x - mid >= 0)                                             // 只判断左侧部分的点
                continue;
            x = 0;
            for (j = i + 1; j <= i + 6 + x && j < k; j++)            //只需与有序的领接的的6个点进行比较
            {
                if (points3Sorted[j].x - mid < 0) {//  假如i点是位于mid左边则只需判断在mid右边的j点即可
                    x++;
                    continue;
                }
                if (distanceOfPoints(points3Sorted[i], points3Sorted[j]) < distance) {
                    /////如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                    distance = distanceOfPoints(points3Sorted[i], points3Sorted[j]);
                    a = points3Sorted[i];
                    b = points3Sorted[j];
                }
            }
        }
        return distance;
    }

    public static void main(String[] ar) {
        Point[] points = new Point[5];
        Random random = new Random();
        for (int i = 0; i < 4; i++) {
            points[i] = new Point();
            points[i].x = random.nextDouble() * 10;
            points[i].y = random.nextDouble() * 10;
        }
        ClosestPair closestPair = new ClosestPair();
        double distence = closestPair.cloest(points);
        System.out.println(distence);
        System.out.println("x:" + closestPair.a.x + " y: " + closestPair.a.y);
        System.out.println("x:" + closestPair.b.x + " y: " + closestPair.b.y);
    }

}
