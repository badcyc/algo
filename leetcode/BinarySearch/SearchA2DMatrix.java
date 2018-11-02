package dataStructure.leetcode.BinarySearch;

/**
 * @program: algo
 * @description: 在２维矩阵里查找
 * @author: Yichao Chen
 * @create: 2018-11-02 13:57
 **/

/**
 * [
 * [1,2,3, 4, 5],
 * [7,8,9,10,11]
 * ]
 */
public class SearchA2DMatrix {
    /**
     * @Description: 常规解题思路，运行代码时间复杂度高，8ms beats 42.48% of java
     * @Param: [matrix, target]
     * @return: boolean
     * @Author: Yichao Chen
     * @Date: 18-11-2
     * @Time: 下午2:52
     **/
    public boolean searchMatrix(int[][] matrix, int target) {
        int j;
        if (matrix.length == 0 || matrix[0].length == 0 || matrix[0][0] > target) return false;
        for (int i = 0; i < matrix.length; i++) {
            if (matrix[i][0] < target) continue;
            if (matrix[i][0] == target) return true;
            for (j = 0; j < matrix[i].length; j++) {
                if (matrix[i - 1][j] < target) continue;
                if (matrix[i - 1][j] == target) return true;
                if (matrix[i - 1][j] > target) return false;
            }
            if (j == matrix[i].length - 1) break;
        }
        for (j = 0; j < matrix[0].length - 1; j++) {
            if (matrix[matrix.length - 1][j] < target) continue;
            if (matrix[matrix.length - 1][j] == target) return true;
            if (matrix[matrix.length - 1][j] > target) break;
        }
        return false;
    }

    /**
     * @Description: 常规结题思路，代码简洁点但时间复杂度没有变，提高效率需要用二分法
     * @Param: [matrix, target]
     * @return: boolean
     * @Author: Yichao Chen
     * @Date: 18-11-2
     * @Time: 下午3:08
     **/
    public boolean search2DMatrix(int[][] matrix, int target) {
        int rowLength = matrix.length;
        if (rowLength == 0) return false;
        int lineLen = matrix[0].length;
        if (lineLen == 0) return false;
        int i;
        if (target > matrix[rowLength - 1][lineLen - 1]) return false;
        for (i = 0; i < rowLength; i++) {
            if (target < matrix[i][0]) return false;
            if (target >= matrix[i][0] && target <= matrix[i][lineLen - 1]) {
                break;
            }

        }
        for (int j = 0; j < lineLen; j++) {
            if (matrix[i][j] == target) return true;
            if (matrix[i][j] > target) return false;
        }
        return false;
    }

    public boolean searchMatrix2Divider(int[][] matrix, int target) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return false;
        }
        int rowLen = matrix.length;
        int colLen = matrix[0].length;
        int start = 0;
        int end = rowLen * colLen - 1;
        while (start + 1 < end) {
            int mid = (start + end) / 2;
            if (matrix[mid / colLen][mid % colLen] == target) return true;
            else if (matrix[mid / colLen][mid % colLen] > target) end = mid;
            else start = mid;
        }
        if (matrix[start / colLen][start % colLen] == target
                || matrix[end / colLen][end % colLen] == target) return true;
        return false;

    }

    public static void main(String[] args) {
        int[][] matrix = {
                {1, 3}
//                {8, 9, 10, 11}
        };
        SearchA2DMatrix searchA2DMatrix = new SearchA2DMatrix();
        boolean result = searchA2DMatrix.searchMatrix2Divider(matrix, 3);
        System.out.println(result);
    }
}
