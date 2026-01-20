/*
 Problem: Cheapest Flights Within K Stops

 Approach:
 - Build adjacency list for the flight graph
 - Use BFS with a queue storing {stops, {node, cost}}
 - Track minimum cost to reach each node
 - Only continue traversal if stops <= K
 - Update distance only when a cheaper cost is found

 Time Complexity: O(E * K)
 Space Complexity: O(V + E)
*/

class Solution {
public:
    int findCheapestPrice(int n,
                           vector<vector<int>>& flights,
                           int src, int dst, int k) {

        // Step 1: Build adjacency list (u -> {v, cost})
        vector<vector<pair<int, int>>> adj(n);
        for (auto &flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }
        // Step 2: Distance array
        vector<int> dist(n, 1e9);
        dist[src] = 0;
        // Step 3: Queue for BFS: {stops, {node, cost}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            int stops = cur.first;
            int node = cur.second.first;
            int cost = cur.second.second;
            // Stop if number of stops exceeds limit
            if (stops > k) continue;
            for (auto &edge : adj[node]) {
                int nextNode = edge.first;
                int price = edge.second;
                if (cost + price < dist[nextNode]) {
                    dist[nextNode] = cost + price;
                    q.push({stops + 1, {nextNode, dist[nextNode]}});
                }
            }
        }
       if (dist[dst] == 1e9)
            return -1;
        return dist[dst];
    }
};
