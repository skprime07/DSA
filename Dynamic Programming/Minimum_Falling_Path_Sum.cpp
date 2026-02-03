/*
Problem: LeetCode 931 – Minimum Falling Path Sum

Approach:
1. From any cell, you can move to directly below, below-left, or below-right.
2. For every cell, add its value to the minimum of these three possible previous cells.
3. First row is taken as it is (starting points).
4. Build the answer row by row using DP.
5. Final result is the minimum value in the last row.
6. Space optimized version keeps only the previous row.

Time Complexity: O(N * M)
Space Complexity:
Memoization → O(N * M)
Tabulation → O(N * M)
Space Optimized → O(M)
*/

                           //MEMOIZATION:
class Solution {
public:
    int f(int i, int j,vector<vector<int>>& matrix, vector<vector<int>>& dp){
        int m = matrix[0].size();
        if(j<0 || j>=m) return 1e9;
        if(i == 0) return matrix[0][j];
        if(dp[i][j] != -1) return dp[i][j];
        int s = matrix[i][j] + f(i - 1, j, matrix, dp);
        int ld = matrix[i][j] + f(i - 1, j - 1, matrix, dp);
        int rd = matrix[i][j] + f(i - 1, j + 1, matrix, dp);
        return  dp[i][j] = min(s, min(ld, rd));
    }
 
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n , vector<int>(m, -1));
        int mini = 1e9;
        for(int j = 0; j< m; j++){
            mini = min(mini, f(n-1, j, matrix, dp));
        }
        return mini;
    }
};

                         //TABULATION :
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size(); 
        vector<vector<int>> dp(n, vector<int>(m, 0));  
        // Base case: first row is the same
        for (int j = 0; j < m; j++) {
            dp[0][j] = matrix[0][j];
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int s = matrix[i][j] + dp[i-1][j];
                int ld = matrix[i][j] + (j > 0 ? dp[i-1][j-1] : 1e9);
                int rd = matrix[i][j] + (j < m-1 ? dp[i-1][j+1] : 1e9);

                dp[i][j] = min(s, min(ld, rd));
            }
        }
        // Get the minimum in the last row
        int mini = 1e9;
        for (int j = 0; j < m; j++) {
            mini = min(mini, dp[n-1][j]);
        }

        return mini;
    }
};

       
                             //SPACE OPTIMISED:
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> prev(m, 0);
        // Base case: copy first row
        for (int j = 0; j < m; j++) {
            prev[j] = matrix[0][j];
        }
        for (int i = 1; i < n; i++) {
            vector<int> curr(m, 0);
            for (int j = 0; j < m; j++) {
                int s = matrix[i][j] + prev[j];
                int ld = matrix[i][j] + (j > 0 ? prev[j - 1] : 1e9);
                int rd = matrix[i][j] + (j < m - 1 ? prev[j + 1] : 1e9);
                curr[j] = min(s, min(ld, rd));
            }
            prev = curr;
        }
        // Minimum in the last processed row
        int mini = *min_element(prev.begin(), prev.end());
        return mini;
    }
};
