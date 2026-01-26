/*
 Problem: Next Greater Element II (Circular Array)

 Approach:
 - Use monotonic stack storing indices
 - Traverse array twice (2*n) from right to left
 - Use modulo (%) to simulate circular behavior
 - For each index, pop smaller/equal elements
 - Top of stack gives next greater element

 Time Complexity: O(N)
 Space Complexity: O(N)
*/

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);   // initialize with -1
        stack<int> s;               // stack stores indices
        for (int i = 2 * n - 1; i >= 0; i--) {
            int index = i % n;
            while (!s.empty() && nums[s.top()] <= nums[index]) {
                s.pop();
            }
            if (!s.empty()) {
                result[index] = nums[s.top()];
            }
            s.push(index);
        }
        return result;
    }
};
