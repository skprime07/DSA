/*
 Problem: Shortest Path in Binary Matrix

 Approach:
 - Use Breadth First Search (BFS) since all moves have equal cost
 - Start from (0, 0) and explore in 8 possible directions
 - Maintain a distance matrix to track shortest path length
 - First time reaching destination gives the shortest path

 Time Complexity: O(N * N)
 Space Complexity: O(N * N)
*/

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        // If start or end cell is blocked
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;
        // Distance matrix
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        // Queue stores {distance, {row, col}}
        queue<pair<int, pair<int, int>>> q;
        dist[0][0] = 1;
        q.push({1, {0, 0}});
        // 8 possible directions
        int dRow[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
        int dCol[8] = {-1,  0,  1, -1, 1,-1, 0, 1};
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            int curDist = cur.first;
            int row = cur.second.first;
            int col = cur.second.second;
            // Destination reached
            if (row == n - 1 && col == n - 1)
                return curDist;
            // Explore neighbors
            for (int i = 0; i < 8; i++) {
                int newRow = row + dRow[i];
                int newCol = col + dCol[i];
                if (newRow >= 0 && newRow < n &&
                    newCol >= 0 && newCol < n &&
                    grid[newRow][newCol] == 0 &&
                    curDist + 1 < dist[newRow][newCol]) {
                    dist[newRow][newCol] = curDist + 1;
                    q.push({curDist + 1, {newRow, newCol}});
                }
            }
        }
        return -1; // No valid path
    }
};
