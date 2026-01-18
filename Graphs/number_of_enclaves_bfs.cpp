/*
 Problem: Number of Enclaves

 Approach:
 - Perform multi-source BFS from all boundary land cells
 - Mark all land cells connected to the boundary as visited
 - Count remaining unvisited land cells (enclaves)

 Time Complexity: O(N * M)
 Space Complexity: O(N * M)
*/

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));
        queue<pair<int, int>> q;

        // Push all boundary land cells into queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
              // first row, first col, last row, last col 
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    if (grid[i][j] == 1) {
                        q.push({i, j});
                        visited[i][j] = 1;
                    }
                }
            }
        }
        int dRow[4] = {-1, 0, 1, 0};
        int dCol[4] = {0, 1, 0, -1};
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int newRow = row + dRow[i];
                int newCol = col + dCol[i];

                if (newRow >= 0 && newRow < n &&
                    newCol >= 0 && newCol < m &&
                    grid[newRow][newCol] == 1 &&
                    !visited[newRow][newCol]) {

                    visited[newRow][newCol] = 1;
                    q.push({newRow, newCol});
                }
            }
        }

        // Count unvisited land cells
        int enclaves = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !visited[i][j])
                    enclaves++;
            }
        }

        return enclaves;
    }
};
