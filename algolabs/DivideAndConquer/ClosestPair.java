package dataStructure.algolabs.DivideAndConquer;


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
    class MyComparator implements Comparator<Point> {
        @Override
        public int compare(Point o1, Point o2) {
            return compareXY(o1, o2);
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
        Arrays.sort(points, new MyComparator());
        return points;
    }

    Point a = new Point(), b = new Point();

    public double cloest(Point[] points) {
        Point[] pointsSorted = sort(points);
        return cloestPair(pointsSorted);
    }

//    Point a, b;

    private double cloestPair(Point[] points) {
        if (points.length == 1) {
            return Integer.MAX_VALUE;
        }
        //两点
        if (points.length == 2) {
            a.x = points[0].x;
            a.y = points[0].y;
            b.x = points[1].x;
            b.y = points[1].y;
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
                if (distanceOfPoints(a, b) > d1) {
                    a.x = points[0].x;
                    a.y = points[0].y;
                    b.x = points[1].x;
                    b.y = points[1].y;
                }
                return d;
            }
            if (d == d2) {
                if (distanceOfPoints(a, b) > d2) {
                    a.x = points[0].x;
                    a.y = points[0].y;
                    b.x = points[1].x;
                    b.y = points[1].y;
                }
                return d;
            }
            if (d == d3) {
                if (distanceOfPoints(a, b) > d3) {
                    a.x = points[0].x;
                    a.y = points[0].y;
                    b.x = points[1].x;
                    b.y = points[1].y;
                }
                return d3;
            }
        }
        //多于三点 分治
        double ld;
        double rd;
        double distance;
        int lLength = (points.length - 1) / 2;
        double mid;
        mid = points[lLength].x;
        Point[] lps = new Point[lLength];
        Point[] rps = new Point[points.length - lLength];
        int index;
        for (index = 0; index < lLength; index++) {
            lps[index] = points[index];
        }
        for (int index1 = 0; index < points.length; index++) {
            rps[index1++] = points[index];
        }
        ld = cloestPair(lps);
        rd = cloestPair(rps);
        //todo
        if (ld < rd) {
            distance = ld;
        } else {
            distance = rd;
        }
        //todo
        int i = lLength;
        int k = 0;
        while (i >= 0 && mid - points[i].x >= distance) {
            k++;
            i--;
        }
        i = lLength + 1;
        while (i < points.length && points[i].x - mid <= distance) {
            k++;
            i++;
        }
        Point[] points3 = new Point[k];
        i = lLength;
        k = 0;
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
            if (j < k && points3Sorted[j].x - mid >= 0)                                             // 只判断左侧部分的点
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
                    a.x = points3Sorted[i].x;
                    a.y = points3Sorted[i].y;
                    b.x = points3Sorted[j].x;
                    b.y = points3Sorted[j].y;
                }
            }
        }
        return distance;
    }

    public static void main(String[] ar) {
        Point[] points = new Point[5];
        Random random = new Random();
        for (int i = 0; i < 5; i++) {
            points[i] = new Point();
        }
        points[0].x = 0;
        points[0].y = 1;
        points[1].x = 2;
        points[1].y = 5;
        points[2].x = -1;
        points[2].y = 6;
        points[3].x = -1;
        points[3].y = -2;
        points[4].x = 3;
        points[4].y = 5;


        ClosestPair closestPair = new ClosestPair();
        double distence = closestPair.cloest(points);
        System.out.println(distence);
        System.out.println("x:" + closestPair.a.x + " y: " + closestPair.a.y);
        System.out.println("x:" + closestPair.b.x + " y: " + closestPair.b.y);
    }

}
