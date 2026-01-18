/*
 Problem: Rotten Oranges

 Approach:
 - Use Multi-source BFS
 - Push all initially rotten oranges into the queue with time = 0
 - From each rotten orange, rot adjacent fresh oranges
 - Track the maximum time taken
 - If any fresh orange remains, return -1

 Time Complexity: O(N * M)
 Space Complexity: O(N * M)
*/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int, int>, int>> q;
        vector<vector<int>> visited(n, vector<int>(m, 0));

        // Add all initially rotten oranges to the queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                    visited[i][j] = 2;
                }
            }
        }

        int time = 0;

        // Directions: up, right, down, left
        int dRow[4] = {-1, 0, 1, 0};
        int dCol[4] = {0, 1, 0, -1};

        while (!q.empty()) {
            int row = q.front().first.first;
            int col = q.front().first.second;
            int curTime = q.front().second;
            q.pop();

            time = max(time, curTime);

            for (int i = 0; i < 4; i++) {
                int newRow = row + dRow[i];
                int newCol = col + dCol[i];

                if (newRow >= 0 && newRow < n &&
                    newCol >= 0 && newCol < m &&
                    grid[newRow][newCol] == 1 &&
                    visited[newRow][newCol] != 2) {

                    visited[newRow][newCol] = 2;
                    q.push({{newRow, newCol}, curTime + 1});
                }
            }
        }

        // Check if any fresh orange remains
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && visited[i][j] != 2)
                    return -1;
            }
        }

        return time;
    }
};
