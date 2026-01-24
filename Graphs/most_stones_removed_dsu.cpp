/*
 Problem: Most Stones Removed with Same Row or Column

 Approach:
 - Treat each row and column as separate nodes
 - Offset column indices to avoid collision with row indices
 - Use Disjoint Set Union (Union-Find) to connect row and column of each stone
 - Count number of connected components among used nodes
 - Answer = total stones - number of connected components

 Time Complexity: O(N * α(N))
 Space Complexity: O(N)
*/

class DisjointSet {
public:
    vector<int> parent, rank, size;
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }
    // Find with path compression
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
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        int maxRow = 0, maxCol = 0;
        // Find maximum row and column index
        for (auto &stone : stones) {
            maxRow = max(maxRow, stone[0]);
            maxCol = max(maxCol, stone[1]);
        }
        // DSU size = rows + columns + 1
        DisjointSet ds(maxRow + maxCol + 1);
        unordered_set<int> usedNodes;
        // Union row node with column node
        for (auto &stone : stones) {
            int rowNode = stone[0];
            int colNode = stone[1] + maxRow + 1;

            ds.unionBySize(rowNode, colNode);
            usedNodes.insert(rowNode);
            usedNodes.insert(colNode);
        }
        // Count number of connected components
        int components = 0;
        for (int node : usedNodes) {
            if (ds.findUPar(node) == node)
                components++;
        }
        return n - components;
    }
};
