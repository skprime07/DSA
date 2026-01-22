/*
 Problem: Floyd Warshall Algorithm

 Approach:
 - Floyd–Warshall computes shortest paths between all pairs of vertices
 - Convert -1 (no edge) to a large value (infinity)
 - Use three nested loops to relax paths via intermediate nodes
 - Convert unreachable distances back to -1

 Time Complexity: O(V^3)
 Space Complexity: O(1)   // In-place modification
*/

class Solution {
public:
    void shortest_distance(vector<vector<int>>& matrix) {
        int n = matrix.size();
        const int INF = 1e9;
        // Step 1: Replace -1 with INF and set diagonal to 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1)
                    matrix[i][j] = INF;
                if (i == j)
                    matrix[i][j] = 0;
            }
        }
        // Step 2: Floyd–Warshall Algorithm
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    if (matrix[i][k] < INF && matrix[k][j] < INF) {
                        matrix[i][j] = min(
                            matrix[i][j],
                            matrix[i][k] + matrix[k][j]
                        );
                    }
                }
            }
        }
        // Step 3: Convert INF back to -1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == INF)
                    matrix[i][j] = -1;
            }
        }
    }
};
