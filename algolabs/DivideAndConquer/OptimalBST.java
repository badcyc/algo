package dataStructure.algolabs.DivideAndConquer;

/**
 * @program: algo
 * @description:
 * @author: Yichao Chen
 * @create: 2018-11-12 15:29
 **/
public class OptimalBST {

    private int[][] root;
    private double[][] w;
    private double[][] e;

    public void op(double[] p, double[] q, int n) {
        root = new int[n+1][n+1];
        w = new double[n + 2][n + 1];
        e = new double[n + 2][n + 1];
        for (int i = 1; i <= n + 1; i++) {
            e[i][i - 1] = q[i - 1];
            w[i][i - 1] = q[i - 1];
        }
        for (int l = 1; l <= n; l++) {
            for (int i = 1; i <= n - l + 1; i++) {
                int j = i + l - 1;
                e[i][j] = Integer.MAX_VALUE;
                w[i][j] = w[i][j - 1] + p[j] + q[j];
                for (int r = i; r <= j; r++) {
                    double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                    if (t < e[i][j]) {
                        e[i][j] = t;
                        root[i][j] = r;
                    }
                }
            }
        }
    }

    public void print() {
        for (int i = 0; i < root.length; i++) {
            for (int j = 0; j < root[0].length; j++) {
                System.out.print(root[i][j] + " ");
            }
            System.out.println();
        }

        for (int i = 0; i < w.length; i++) {
            for (int j = 0; j < w[0].length; j++) {
                System.out.print(w[i][j] + " ");
            }
            System.out.println();
        }

        for (int i = 0; i < e.length; i++) {
            for (int j = 0; j < e[0].length; j++) {
                System.out.print(e[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void construct_optimal_bst(int i, int j, int flag) {
//        if ()
        if (i <= j) {
            if (flag == 1) {
                System.out.println("k" + root[i][j] + "为根");
            } else if (flag == 0) {
                System.out.println("k" + root[i][j] + "为k" + (j + 1) + "的左孩子");
            } else {
                System.out.println("k" + root[i][j] + "为k" + (i - 1) + "的右孩子");
            }
            construct_optimal_bst(i, root[i][j] - 1, 0);
            construct_optimal_bst(root[i][j] + 1, j, 2);
        } else if (i - 1 == j) {
            if (flag == 0) {
                System.out.println("d" + j + "为k" + (j + 1) + "的左孩子");
            } else {
                System.out.println("d" + j + "为k" + (i - 1) + "的右孩子");
            }
        }
    }

    public static void main(String[] args) {
        OptimalBST optimalBST = new OptimalBST();
        double[] p = {0, 0.15, 0.10, 0.05, 0.10, 0.20};
        double[] q = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
        optimalBST.op(p, q, 5);
        optimalBST.print();
        optimalBST.construct_optimal_bst(1,5,1);
    }
}
