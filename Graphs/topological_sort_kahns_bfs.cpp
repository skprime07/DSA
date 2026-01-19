/*
 Problem: Topological Sort

 Approach (Kahn's Algorithm):
 - Compute indegree of all vertices
 - Push all vertices with indegree 0 into a queue
 - Repeatedly remove nodes from queue and reduce indegree of neighbors
 - When a neighbor’s indegree becomes 0, push it into the queue
 - Resulting order is a valid topological ordering

 Time Complexity: O(V + E)
 Space Complexity: O(V)
*/

class Solution {
public:
    vector<int> topoSort(int V, vector<int> adj[]) {

        vector<int> indegree(V, 0);
        // Calculate indegree of each node
        for (int i = 0; i < V; i++) {
            for (int neighbour : adj[i]) {
                indegree[neighbour]++;
            }
        }
        queue<int> q;
        // Push all nodes with indegree 0
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topoOrder;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);
            // Reduce indegree of adjacent nodes
            for (int neighbour : adj[node]) {
                indegree[neighbour]--;
                if (indegree[neighbour] == 0) {
                    q.push(neighbour);
                }
            }
        }

        return topoOrder;
    }
};
