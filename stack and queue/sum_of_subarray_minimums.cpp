/*
 Problem: Sum of Subarray Minimums

 Approach:
 - Use monotonic stack
 - Find Previous Less Element (PLE)
 - Find Next Less Element (NLE)
 - Each element contributes:
     arr[i] * (i - PLE[i]) * (NLE[i] - i)

 Time Complexity: O(N)
 Space Complexity: O(N)
*/

class Solution {
public:
    
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        vector<int> ple(n), nle(n); // Previous Less Element, Next Less Element
        stack<int> s;
        // Calculate PLE
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && arr[s.top()] > arr[i])
                s.pop();

            ple[i] = s.empty() ? -1 : s.top();
            s.push(i);
        }
        // Clear stack
        while (!s.empty()) s.pop();
        // Calculate NLE
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && arr[s.top()] >= arr[i])
                s.pop();

            nle[i] = s.empty() ? n : s.top();
            s.push(i);
        }
        // Compute answer
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            long long left = i - ple[i];
            long long right = nle[i] - i;
            result = (result + arr[i] * left % MOD * right % MOD) % MOD;
        }
        return (int)result;
    }
};
