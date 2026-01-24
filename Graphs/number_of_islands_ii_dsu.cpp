/*
 Problem: Number of Islands II

 Approach:
 - Use Disjoint Set Union (DSU) to dynamically connect land cells
 - Convert 2D grid cell (row, col) to 1D node = row * m + col
 - Each operator turns water into land
 - For each new land, union it with its adjacent lands
 - Track number of connected components (islands)

 Time Complexity: O(Q * α(N*M))
 Space Complexity: O(N*M)
*/

class DisjointSet {
public:
    vector<int> parent, rank, size;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    // Union by size
    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);
        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};
class Solution {
private:
    // Check valid grid cell
    bool isValid(int r, int c, int n, int m) {
        return r >= 0 && r < n && c >= 0 && c < m;
    }
public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>>& operators) {
        DisjointSet ds(n * m);
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int islandCount = 0;
        vector<int> result;
        // Directions: up, right, down, left
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};
        for (auto &op : operators) {
            int row = op[0];
            int col = op[1];
            // If already land, island count doesn't change
            if (vis[row][col] == 1) {
                result.push_back(islandCount);
                continue;
            }
            // Convert water to land
            vis[row][col] = 1;
            islandCount++;
            int node = row * m + col;
            // Check all 4 neighbors
            for (int k = 0; k < 4; k++) {
                int newRow = row + dr[k];
                int newCol = col + dc[k];
                if (isValid(newRow, newCol, n, m) && vis[newRow][newCol] == 1) {
                    int adjNode = newRow * m + newCol;
                    if (ds.findUPar(node) != ds.findUPar(adjNode)) {
                        islandCount--;
                        ds.unionBySize(node, adjNode);
                    }
                }
            }
            result.push_back(islandCount);
        }

        return result;
    }
};
