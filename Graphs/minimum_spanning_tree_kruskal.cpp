/*
 Problem: Minimum Spanning Tree (Kruskal's Algorithm)

 Approach:
 - Use Kruskal’s Algorithm
 - Sort all edges by weight
 - Use Disjoint Set Union (Union-Find) to avoid cycles
 - Pick the smallest edge that connects two different components

 Time Complexity: O(E log E)
 Space Complexity: O(V + E)
*/

class DisjointSet {
private:
    vector<int> parent, rank, size;

public:
    // Constructor
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
    // Function to get sum of weights of edges of the MST
    int spanningTree(int V, vector<vector<int>> adj[]) {
        vector<pair<int, pair<int, int>>> edges;
        for (int u = 0; u < V; u++) {
            for (auto &it : adj[u]) {
                int v = it[0];
                int wt = it[1];
                edges.push_back({wt, {u, v}});
            }
        }
        // Sort edges by weight
        sort(edges.begin(), edges.end());
        DisjointSet ds(V);
        int mstSum = 0;
        for (auto &edge : edges) {
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstSum += wt;
                ds.unionBySize(u, v);
            }
        }

        return mstSum;
    }
};
