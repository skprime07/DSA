/*
Problem: Find the Celebrity (GFG / LeetCode Variant)

Approach:
- Use two pointers (top and down).
- Eliminate non-celebrities:
    → If top knows down, top cannot be celebrity.
    → Else if down knows top, down cannot be celebrity.
    → Else eliminate both.
- After loop, only one potential candidate remains.
- Validate this candidate:
    → Candidate should NOT know anyone.
    → Everyone should know candidate.

Time Complexity: O(N)
Space Complexity: O(1)
*/

int findCelebrity(vector<vector<int>>& mat, int n) {
    int top = 0, down = n - 1;
    // Step 1: Find potential celebrity
    while (top < down) {
        // If top knows down, top can't be celebrity
        if (mat[top][down] == 1) {
            top++;
        }
        // If down knows top, down can't be celebrity
        else if (mat[down][top] == 1) {
            down--;
        }
        // Both don't know each other → eliminate both
        else {
            top++;
            down--;
        }
    }
    // No candidate found
    if (top > down) return -1;
    // Step 2: Validate candidate
    for (int i = 0; i < n; i++) {
        if (i == top) continue;
        // Celebrity should not know anyone
        // Everyone should know celebrity
        if (mat[top][i] == 1 || mat[i][top] == 0)
            return -1;
    }
    return top;
}
