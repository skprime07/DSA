/*
Problem: LeetCode 64 – Minimum Path Sum
Link: https://leetcode.com/problems/minimum-path-sum/

Approach:
1. From each cell, you can only come from top or left.
2. Add current cell value with minimum of top/left.
3. Use DP to store minimum sum till each cell.
4. Memoization uses recursion + dp table.
5. Tabulation fills dp grid iteratively.
6. Space optimized version keeps only previous row.

Time Complexity: O(M * N)
Space Complexity:
Memoization → O(M * N)
Tabulation → O(M * N)
Space Optimized → O(N)
*/

                                    //MEMOIZATION :
class Solution {
public: 
    int f(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp){
        if(i == 0 && j ==0) return grid[0][0];
        if(i < 0 || j < 0) return 1e9;
        if(dp[i][j] != -1) return dp[i][j];
        int up = grid[i][j] + f(i - 1, j, grid, dp);
        int left = grid[i][j] + f(i, j - 1, grid, dp);
        return min(up,left);
    }

    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return f(m - 1, n - 1, grid, dp);
    }
};

                                     //TABULATION:
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();     
        int n = grid[0].size();  

        vector<vector<int>> dp(m, vector<int>(n, 0)); 

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {

                if(i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                } else {
                    int fromTop;
                    if(i > 0) {
                        fromTop = dp[i - 1][j];
                    } else {
                        fromTop = 1e9;
                    }
                    int fromLeft;
                    if(j > 0) {
                        fromLeft = dp[i][j - 1];
                    } else {
                        fromLeft = 1e9;
                    }
                    dp[i][j] = grid[i][j] + min(fromTop, fromLeft);
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};

                                   //SPACE OPTIMISED:
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> prev(n, 0);  // Store the previous row

        for (int i = 0; i < m; i++) {
            vector<int> curr(n, 0);  // Current row

            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    curr[j] = grid[i][j];  // Starting cell
                } else {
                    int fromTop = (i > 0) ? prev[j] : 1e9;
                    int fromLeft = (j > 0) ? curr[j - 1] : 1e9;

                    curr[j] = grid[i][j] + min(fromTop, fromLeft);
                }
            }

            prev = curr;  // Move to the next row
        }

        return prev[n - 1];  // Last cell has the answer
    }
};
