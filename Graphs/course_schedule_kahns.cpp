/*
 Problem: Course Schedule

 Approach (Kahn's Algorithm - BFS):
 - Treat courses as nodes and prerequisites as directed edges
 - Build adjacency list from prerequisites
 - Compute indegree of each node
 - Push all nodes with indegree 0 into queue
 - Perform BFS and count processed nodes
 - If all nodes are processed, no cycle exists → courses can be finished

 Time Complexity: O(V + E)
 Space Complexity: O(V + E)
*/

class Solution {
public:
    bool canFinish(int V, vector<vector<int>>& prerequisites) {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(V);
        for (auto &edge : prerequisites) {
            adj[edge[1]].push_back(edge[0]);
        }
        // Step 2: Calculate indegree
        vector<int> indegree(V, 0);
        for (int i = 0; i < V; i++) {
            for (int neighbour : adj[i]) {
                indegree[neighbour]++;
            }
        }
        // Step 3: Push all nodes with indegree 0
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        // Step 4: Kahn's BFS
        int processed = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            processed++;
            for (int neighbour : adj[node]) {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0) {
                    q.push(neighbour);
                }
            }
        }
        // If all courses are processed, return true
        return processed == V;
    }
};
