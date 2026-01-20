/*
 Problem: Shortest Path in Directed Acyclic Graph (DAG)

 Approach:
 - Build adjacency list with weights
 - Perform Topological Sort using Kahn’s Algorithm
 - Initialize distance array with infinity
 - Relax edges in topological order
 - Replace unreachable nodes with -1

 Time Complexity: O(V + E)
 Space Complexity: O(V + E)
*/

class Solution {
public:
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list (node -> {neighbour, weight})
        vector<vector<pair<int,int>>> adj(V);
        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
        }
        // Step 2: Topological Sort (Kahn's Algorithm)
        vector<int> indegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (auto &p : adj[i]) {
                indegree[p.first]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }
        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for (auto &p : adj[node]) {
                indegree[p.first]--;
                if (indegree[p.first] == 0)
                    q.push(p.first);
            }
        }
        // Step 3: Distance array
        vector<int> dist(V, 1e9);
        dist[0] = 0;   // source node = 0
        // Step 4: Relax edges in topo order
        for (int node : topo) {
            if (dist[node] != 1e9) {
                for (auto &p : adj[node]) {
                    int v = p.first;
                    int wt = p.second;
                    if (dist[node] + wt < dist[v]) {
                        dist[v] = dist[node] + wt;
                    }
                }
            }
        }
        // Step 5: Mark unreachable nodes
        for (int i = 0; i < V; i++) {
            if (dist[i] == 1e9)
                dist[i] = -1;
        }

        return dist;
    }
};
