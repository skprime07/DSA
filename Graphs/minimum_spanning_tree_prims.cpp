/*
 Problem: Minimum Spanning Tree (Prim's Algorithm)

 Approach:
 - Use Prim’s Algorithm with a Min-Heap (Priority Queue)
 - Start from node 0
 - Always pick the edge with minimum weight that connects
   a visited node to an unvisited node
 - Add its weight to MST sum and mark the node as visited

 Time Complexity: O(E log V)
 Space Complexity: O(V + E)
*/

class Solution {
public:
    int spanningTree(int V, vector<vector<int>> adj[]) {
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;
        vector<int> visited(V, 0);
        // Start from node 0
        pq.push({0, 0});
        int mstSum = 0;
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int weight = cur.first;
            int node = cur.second;
            if (visited[node])
                continue;
            // Include this node in MST
            visited[node] = 1;
            mstSum += weight;
            // Traverse adjacent nodes
            for (auto &edge : adj[node]) {
                int adjNode = edge[0];
                int edgeWeight = edge[1];
                if (!visited[adjNode]) {
                    pq.push({edgeWeight, adjNode});
                }
            }
        }
        return mstSum;
    }
};
