package dataStructure.DynamicProgram;

/**
 * @program: algo
 * @description:A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
 * <p>
 * The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
 * <p>
 * Now consider if some obstacles are added to the grids. How many unique paths would there be?
 * @author: Yichao Chen
 * @create: 2018-10-31 16:57
 * <p>
 * Input:
 * [
 * [0,0,0],
 * [0,1,0],
 * [0,0,0]
 * ]
 * Output: 2
 * Explanation:
 * There is one obstacle in the middle of the 3x3 grid above.
 * There are two ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down -> Down
 * 2. Down -> Down -> Right -> Right
 * <p>
/**
 * [
 *      [0,0,0,0,0,0],
 *      [0,0,0,0,1,0],
 *      [0,0,0,0,1,0]
 * ]
 */
public class UniquePath {
    /**
     * @Description: 递归的算法解决，但时间复杂度太高 leetcode 提示 time limit
     * @Param: [obstacleGrid]
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-31
     * @Time: 下午7:55
     **/
    public int uniquePathsWithObstacles(int[][] obstacleGrid) {
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }
        if (obstacleGrid.length == 1 && obstacleGrid[0].length == 1 && obstacleGrid[0][0] == 0) {
            return 1;
        }
        if ((obstacleGrid.length == 1 && obstacleGrid[0].length == 2
                && obstacleGrid[0][1] == 0)
                ||
                (obstacleGrid.length == 2 && obstacleGrid[0].length == 1
                        && obstacleGrid[1][0] == 0)) {
            return 1;
        }
        int k1 = 0, k2 = 0;
        if (obstacleGrid[0].length >= 2 && obstacleGrid[0][1] == 0) {
            int[][] newobs = new int[obstacleGrid.length][obstacleGrid[0].length - 1];
            for (int j = 0; j < obstacleGrid.length; j++) {
                for (int i = 1; i < obstacleGrid[0].length; i++) {
                    newobs[j][i - 1] = obstacleGrid[j][i];
                }
            }
            k1 += uniquePathsWithObstacles(newobs);
        }
        if (obstacleGrid.length >= 2 && obstacleGrid[1][0] == 0) {
            int[][] newobs = new int[obstacleGrid.length - 1][obstacleGrid[0].length];
            for (int i = 1; i < obstacleGrid.length; i++) {
                for (int j = 0; j < obstacleGrid[0].length; j++) {
                    newobs[i - 1][j] = obstacleGrid[i][j];
                }
            }
            k2 += uniquePathsWithObstacles(newobs);
        }
        return k1 + k2;
    }

    /**
     * @Description: 递归的算法解决，添加备忘录，没有尝试提交
     * @Param: [obstacleGrid]
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-31
     * @Time: 下午7:55
     **/
    public int[][] mem = new int[20][20];

    int[][] obst;

    public void setObst(int[][] obst) {
        this.obst = obst;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                mem[i][j] = -1;
            }
        }
    }

    public int uniquePathsWithObstaclesWithMem(int[][] obstacleGrid) {
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }
        if (obstacleGrid.length == 1 && obstacleGrid[0].length == 1 && obstacleGrid[0][0] == 0) {
            return 1;
        }
        if ((obstacleGrid.length == 1 && obstacleGrid[0].length == 2
                && obstacleGrid[0][1] == 0)
                ||
                (obstacleGrid.length == 2 && obstacleGrid[0].length == 1
                        && obstacleGrid[1][0] == 0)) {
            return 1;
        }
        int k1 = 0, k2 = 0;
        if (mem[obst.length - obstacleGrid.length][obst[0].length - obstacleGrid[0].length] != -1) {
            return mem[obst.length - obstacleGrid.length][obst[0].length - obstacleGrid[0].length];
        }
        if (obstacleGrid[0].length >= 2 && obstacleGrid[0][1] == 0) {
            int[][] newobs = new int[obstacleGrid.length][obstacleGrid[0].length - 1];
            for (int j = 0; j < obstacleGrid.length; j++) {
                for (int i = 1; i < obstacleGrid[0].length; i++) {
                    newobs[j][i - 1] = obstacleGrid[j][i];
                }
            }
            k1 += uniquePathsWithObstaclesWithMem(newobs);
            mem[this.obst.length - newobs.length][this.obst[0].length - newobs[0].length] = k1;
        }
        if (obstacleGrid.length >= 2 && obstacleGrid[1][0] == 0) {
            int[][] newobs = new int[obstacleGrid.length - 1][obstacleGrid[0].length];
            for (int i = 1; i < obstacleGrid.length; i++) {
                for (int j = 0; j < obstacleGrid[0].length; j++) {
                    newobs[i - 1][j] = obstacleGrid[i][j];
                }
            }
            k2 += uniquePathsWithObstaclesWithMem(newobs);
            mem[obst.length - newobs.length][obst[0].length - newobs[0].length] = k2;
        }
        return k1 + k2;
    }


    /**
     * @Description: 自底向上的动态规划，leetcode 成功，但时间复杂度依旧很高 bits 49.59%,垃圾
     * @Param: [obstacleGrid]
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-31
     * @Time: 下午8:48
     **/
    public int BottomUpuniquePathsWithObstacles(int[][] obstacleGrid) {
        int[][] obs = new int[obstacleGrid.length][obstacleGrid[0].length];
        for (int i = obstacleGrid.length - 1; i >= 0; --i) {
            for (int j = obstacleGrid[0].length - 1; j >= 0; --j) {
                obs[i][j] = 0;
                if (i == obstacleGrid.length - 1 && j == obstacleGrid[0].length - 1 && obstacleGrid[i][j] == 0) {
                    obs[i][j] = 1;
                }
                if (i + 1 < obstacleGrid.length && j + 1 < obstacleGrid[0].length && obstacleGrid[i][j] == 0) {
                    obs[i][j] = obs[i + 1][j] + obs[i][j + 1];
                }
                if (j + 1 == obstacleGrid[0].length && i + 1 < obstacleGrid.length && obstacleGrid[i][j] == 0) {
                    obs[i][j] += obs[i + 1][j];
                }
                if (i + 1 == obstacleGrid.length && j + 1 < obstacleGrid[0].length && obstacleGrid[i][j] == 0) {
                    obs[i][j] += obs[i][j + 1];
                }
            }
        }
        return obs[0][0];
    }

    /**
     * @Description: leetcode 答案
     * @Param: [obstacleGrid]
     * @return: int
     * @Author: Yichao Chen
     * @Date: 18-10-31
     * @Time: 下午9:03
     **/
    public int others(int[][] obstacleGrid) {

        int R = obstacleGrid.length;
        int C = obstacleGrid[0].length;

        // If the starting cell has an obstacle, then simply return as there would be
        // no paths to the destination.
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }

        // Number of ways of reaching the starting cell = 1.
        obstacleGrid[0][0] = 1;

        // Filling the values for the first column
        for (int i = 1; i < R; i++) {
            obstacleGrid[i][0] = (obstacleGrid[i][0] == 0 && obstacleGrid[i - 1][0] == 1) ? 1 : 0;
        }

        // Filling the values for the first row
        for (int i = 1; i < C; i++) {
            obstacleGrid[0][i] = (obstacleGrid[0][i] == 0 && obstacleGrid[0][i - 1] == 1) ? 1 : 0;
        }

        // Starting from cell(1,1) fill up the values
        // No. of ways of reaching cell[i][j] = cell[i - 1][j] + cell[i][j - 1]
        // i.e. From above and left.
        for (int i = 1; i < R; i++) {
            for (int j = 1; j < C; j++) {
                if (obstacleGrid[i][j] == 0) {
                    obstacleGrid[i][j] = obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
                } else {
                    obstacleGrid[i][j] = 0;
                }
            }
        }

        // Return value stored in rightmost bottommost cell. That is the destination.
        return obstacleGrid[R - 1][C - 1];
    }

    public static void main(String[] args) {
        int[][] obs = {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        };
        UniquePath uniquePath = new UniquePath();
//        uniquePath.setObst(obs);
        int result = uniquePath.BottomUpuniquePathsWithObstacles(obs);
        System.out.println(result);
    }
}

