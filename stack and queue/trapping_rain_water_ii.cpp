/*
 Problem: Trapping Rain Water II (2D Grid)

 Approach:
 - Use min-heap (priority queue) starting from boundary cells
 - Perform BFS-like expansion
 - Maintain visited matrix
 - For each neighbor:
     → trapped water = max(0, boundaryHeight - cellHeight)
     → push max(boundaryHeight, cellHeight) back into heap

 Time Complexity: O(M*N log(M*N))
 Space Complexity: O(M*N)
*/

class Solution {
public:
    typedef pair<int, pair<int, int>> PP;
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<PP, vector<PP>, greater<>> boundaryCells;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // Push left & right boundaries
        for (int r = 0; r < m; ++r) {
            for (int c : {0, n - 1}) {
                boundaryCells.push({heightMap[r][c], {r, c}});
                visited[r][c] = true;
            }
        }
        // Push top & bottom boundaries
        for (int c = 0; c < n; ++c) {
            for (int r : {0, m - 1}) {
                boundaryCells.push({heightMap[r][c], {r, c}});
                visited[r][c] = true;
            }
        }
        int trappedWater = 0;
        while (!boundaryCells.empty()) {
            auto [height, cell] = boundaryCells.top();
            boundaryCells.pop();
            int i = cell.first;
            int j = cell.second;
            for (vector<int>& dir : directions) {
                int i_ = i + dir[0];
                int j_ = j + dir[1];
                if (i_ >= 0 && i_ < m && j_ >= 0 && j_ < n && !visited[i_][j_]) {
                    trappedWater += max(0, height - heightMap[i_][j_]);
                    boundaryCells.push({
                        max(height, heightMap[i_][j_]),
                        {i_, j_}
                    });
                    visited[i_][j_] = true;
                }
            }
        }
        return trappedWater;
    }
};
