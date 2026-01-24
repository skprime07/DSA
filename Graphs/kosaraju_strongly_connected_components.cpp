/*
 Problem: Strongly Connected Components (Kosaraju's Algorithm)

 Concept:
 - A Strongly Connected Component (SCC) is a group of vertices where
   every vertex is reachable from every other vertex.
 - Kosaraju’s Algorithm finds SCCs using:
   1) DFS with finishing times
   2) Transpose of the graph
   3) DFS in order of decreasing finishing time

 Steps:
 1. Perform DFS and push nodes to stack by finishing time
 2. Reverse all edges (transpose graph)
 3. Pop nodes from stack and DFS on transpose graph
    → Each DFS gives one SCC

 Time Complexity: O(V + E)
 Space Complexity: O(V + E)
*/

class Solution {
private:
    // Step 1: DFS to store nodes by finishing time
    void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &st) {
        vis[node] = 1;
        for (auto neigh : adj[node]) {
            if (!vis[neigh]) {
                dfs(neigh, vis, adj, st);
            }
        }
        st.push(node); // push after visiting all neighbors
    }
    // Step 2: DFS on transposed graph
    void dfsTranspose(int node, vector<int> &vis, vector<int> adjT[]) {
        vis[node] = 1;
        for (auto neigh : adjT[node]) {
            if (!vis[neigh]) {
                dfsTranspose(neigh, vis, adjT);
            }
        }
    }

public:
    int kosaraju(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        stack<int> st;
        // Step 1: DFS and fill stack
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }
        // Step 2: Build transpose graph
        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            vis[i] = 0; // reset visited
            for (auto it : adj[i]) {
                adjT[it].push_back(i);
            }
        }
        // Step 3: Process nodes in stack order
        int sccCount = 0;
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (!vis[node]) {
                sccCount++;
                dfsTranspose(node, vis, adjT);
            }
        }
        return sccCount;
    }
};
