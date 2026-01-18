/*
 Problem: Detect Cycle in an Undirected Graph

 Approach:
 - Use Breadth First Search (BFS)
 - Track parent of each node to detect back-edge
 - If a visited adjacent node is not the parent, a cycle exists

 Time Complexity: O(V + E)
 Space Complexity: O(V)
*/

class Solution {
private:
    bool detectCycleBFS(int src, vector<int> adj[], vector<int>& visited) {
        queue<pair<int, int>> q;
        visited[src] = 1;
        q.push({src, -1});   // {currentNode, parent}

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for (int adjacentNode : adj[node]) {
                if (!visited[adjacentNode]) {
                    visited[adjacentNode] = 1;
                    q.push({adjacentNode, node});
                }
                // If visited and not parent → cycle detected
                else if (adjacentNode != parent) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<int> visited(V, 0);
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (detectCycleBFS(i, adj, visited))
                    return true;
            }
        }
        return false;
    }
};
