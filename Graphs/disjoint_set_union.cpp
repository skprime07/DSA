/*
 Topic: Disjoint Set Union (Union-Find)
 Techniques Used:
 - Path Compression
 - Union by Rank

 Use Cases:
 - Kruskal's Minimum Spanning Tree
 - Cycle Detection in Graphs
 - Dynamic Connectivity Problems

 Time Complexity:
 - Amortized O(α(N)) per operation (almost constant)

 Space Complexity:
 - O(N)
*/

class DisjointSet {
private:
    vector<int> parent, rank;
public:
    // Constructor
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);

        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    // Find with path compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }
    // Union by rank
    void unionByRank(int u, int v) {
        int rootU = findUPar(u);
        int rootV = findUPar(v);
        if (rootU == rootV) return;
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        }
        else if (rank[rootV] < rank[rootU]) {
            parent[rootV] = rootU;
        }
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
};
