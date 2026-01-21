/*
 Problem: Network Delay Time

 Approach:
 - Model the network as a directed weighted graph
 - Use Dijkstra’s Algorithm starting from node k
 - Compute the shortest time to reach all nodes
 - The answer is the maximum distance among all nodes
 - If any node is unreachable, return -1

 Time Complexity: O((V + E) log V)
 Space Complexity: O(V + E)
*/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Step 1: Build adjacency list (u -> {v, weight})
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto &edge : times) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
        }
        // Step 2: Distance array
        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        // Step 3: Min-heap {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;
        pq.push({0, k});
        // Step 4: Dijkstra’s Algorithm
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int curDist = cur.first;
            int node = cur.second;
            // Skip outdated entries
            if (curDist > dist[node])
                continue;
            for (auto &edge : adj[node]) {
                int adjNode = edge.first;
                int weight = edge.second;
                if (curDist + weight < dist[adjNode]) {
                    dist[adjNode] = curDist + weight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        // Step 5: Find maximum distance
        int maxTime = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX)
                return -1;
            maxTime = max(maxTime, dist[i]);
        }
        return maxTime;
    }
};
