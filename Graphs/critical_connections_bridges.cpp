/*
 Problem: Critical Connections in a Network (Bridges in Graph)

 Concept:
 - Use Tarjan's Algorithm to find bridges in an undirected graph
 - A bridge is an edge (u, v) such that removing it disconnects the graph

 Definitions:
 - tin[u]: time of insertion of node u in DFS
 - low[u]: lowest tin reachable from u (including back edges)

 Condition for Bridge:
 - If low[v] > tin[u], then edge (u, v) is a bridge

 Time Complexity: O(V + E)
 Space Complexity: O(V + E)
*/

class Solution {
private:
    int timer = 0;
    void dfs(int node, int parent, vector<int> &vis, vector<int> adj[], vector<int> &tin, vector<int> &low, vector<vector<int>> &bridges) {

        vis[node] = 1;
        tin[node] = low[node] = timer++;
        
        for (auto neigh : adj[node]) {
            if (neigh == parent) continue;

            if (!vis[neigh]) {
                dfs(neigh, node, vis, adj, tin, low, bridges);
                low[node] = min(low[node], low[neigh]);
                // Bridge condition
                if (low[neigh] > tin[node]) {
                    bridges.push_back({node, neigh});
                }
            } else {
                // Back edge
                low[node] = min(low[node], tin[neigh]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n,vector<vector<int>>& connections) {
        vector<int> adj[n];
        for (auto &edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> vis(n, 0);
        vector<int> tin(n, -1), low(n, -1);
        vector<vector<int>> bridges;
        // Graph may be disconnected
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, adj, tin, low, bridges);
            }
        }

        return bridges;
    }
};
