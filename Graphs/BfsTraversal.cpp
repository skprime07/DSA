/*
 Problem: Breadth First Search (BFS) of Graph

 Approach:
 - Start BFS from node 0
 - Use a queue to traverse level by level
 - Maintain a visited array to avoid revisiting nodes

 Time Complexity: O(V + E)
 Space Complexity: O(V)
*/

class Solution {
public:
    // Function to return Breadth First Traversal of the graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        
        vector<int> bfs;          // Stores BFS traversal
        vector<int> visited(V, 0); // Visited array
        
        queue<int> q;
        
        // Start BFS from node 0
        q.push(0);
        visited[0] = 1;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            bfs.push_back(node);
            
            // Traverse all adjacent nodes
            for (int neighbour : adj[node]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = 1;
                    q.push(neighbour);
                }
            }
        }
        
        return bfs;
    }
};
