/*
 Problem: Depth First Search (DFS) of Graph

 Approach:
 - Start DFS from node 0
 - Use recursion to visit nodes depth-wise
 - Maintain a visited array to avoid revisiting nodes

 Time Complexity: O(V + E)
 Space Complexity: O(V)  // recursion stack + visited array
*/

class Solution {
private:
    void dfs(int node, vector<int> adj[], vector<int> &visited, vector<int> &result) {
        visited[node] = 1;
        result.push_back(node);

        // Traverse all adjacent nodes
        for (int neighbour : adj[node]) {
            if (!visited[neighbour]) {
                dfs(neighbour, adj, visited, result);
            }
        }
    }

public:
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        
        vector<int> visited(V, 0);
        vector<int> result;
        dfs(0, adj, visited, result);

        return result;
    }
};
