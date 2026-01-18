/*
 Problem: Surrounded Regions
 Platform: LeetCode
 Link: https://leetcode.com/problems/surrounded-regions/

 Approach:
 - Boundary-connected 'O' cells cannot be flipped
 - Perform DFS from all boundary 'O' cells and mark them as safe
 - Convert remaining unvisited 'O' cells to 'X'

 Time Complexity: O(N * M)
 Space Complexity: O(N * M)   // recursion stack + visited matrix
*/

class Solution {
private:
    void dfs(int row, int col,
             vector<vector<int>> &visited,
             vector<vector<char>> &board,
             int dRow[], int dCol[]) {

        visited[row][col] = 1;
        int n = board.size();
        int m = board[0].size();

        for (int i = 0; i < 4; i++) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (newRow >= 0 && newRow < n &&
                newCol >= 0 && newCol < m &&
                !visited[newRow][newCol] &&
                board[newRow][newCol] == 'O') {

                dfs(newRow, newCol, visited, board, dRow, dCol);
            }
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        if (n == 0) return;
        int m = board[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));

        // Directions: up, right, down, left
        int dRow[4] = {-1, 0, 1, 0};
        int dCol[4] = {0, 1, 0, -1};

        // Traverse first and last row
        for (int j = 0; j < m; j++) {
            // first row
            if (!visited[0][j] && board[0][j] == 'O')
                dfs(0, j, visited, board, dRow, dCol);
            // last row
            if (!visited[n - 1][j] && board[n - 1][j] == 'O')
                dfs(n - 1, j, visited, board, dRow, dCol);
        }

        // Traverse first and last column
        for (int i = 0; i < n; i++) {
          //first col
            if (!visited[i][0] && board[i][0] == 'O')
                dfs(i, 0, visited, board, dRow, dCol);
            //last col
            if (!visited[i][m - 1] && board[i][m - 1] == 'O')
                dfs(i, m - 1, visited, board, dRow, dCol);
        }

        // Convert remaining 'O' to 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && board[i][j] == 'O')
                    board[i][j] = 'X';
            }
        }
    }
};
