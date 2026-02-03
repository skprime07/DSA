/*
Problem: LeetCode 63 – Unique Paths II

Approach:
1. If current cell is an obstacle → paths = 0.
2. Otherwise paths = from top + from left.
3. Use DP to store number of ways to reach each cell.
4. Memoization uses recursion + dp table.
5. Tabulation fills dp grid iteratively.
6. Space optimization keeps only previous row.

Time Complexity: O(M * N)
Space Complexity:
Memoization → O(M * N)
Tabulation → O(M * N)
Space Optimized → O(N)
*/

#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////
// MEMOIZATION
//////////////////////////////////////////////////////////////

int f(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp) {

    if(i < 0 || j < 0) return 0;
    if(grid[i][j] == 1) return 0;
    if(i == 0 && j == 0) return 1;

    if(dp[i][j] != -1) return dp[i][j];

    int up = f(i-1, j, grid, dp);
    int left = f(i, j-1, grid, dp);

    return dp[i][j] = up + left;
}

int uniquePathsWithObstaclesMemo(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return f(m-1, n-1, grid, dp);
}

//////////////////////////////////////////////////////////////
// TABULATION
//////////////////////////////////////////////////////////////

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();       
        int n = obstacleGrid[0].size();   
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                }
                else if(i == 0 && j == 0) {
                    dp[i][j] = 1;
                }

                else {
                    int fromTop = 0;
                    int fromLeft = 0;
                    if(i > 0) {
                        fromTop = dp[i - 1][j];
                    }
                    if(j > 0) {
                        fromLeft = dp[i][j - 1];
                    }
                    dp[i][j] = fromTop + fromLeft;
                }
            }
        }
        return dp[m - 1][n - 1];
    }

//////////////////////////////////////////////////////////////
// SPACE OPTIMIZED
//////////////////////////////////////////////////////////////

class Solution {
private:
    // Function to solve the problem using tabulation
    int func(int m, int n, vector<vector<int>>& matrix) {
        
        vector<int> prev(n, 0), curr(n, 0);
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // Base conditions
                if (matrix[i][j] == 1) {
                    /* If there's an obstacle at the 
                    cell, no paths can pass through it*/
                    curr[j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) {
                    /* If we are at the starting 
                    point, there is one path to it*/
                    curr[j] = 1;
                    continue;
                }

                int up = 0;
                int left = 0;

                /* Check if we can move up and left 
                (if not at the edge of the maze)*/
                if (i > 0)
                    up = prev[j];
                if (j > 0)
                    left = curr[j - 1];

                /* Total number of paths to reach (i, j)
                is the sum of paths from above and left*/
                curr[j] = up + left;
            }
            
            prev = curr;
        }

        /* The final result is stored in dp[m-1][n-1],
        which represents the destination*/
        return prev[n-1];
    }
