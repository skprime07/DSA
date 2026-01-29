/*
Problem: LeetCode 239 – Sliding Window Maximum

Approach:
- Use a deque to store indices of elements.
- Maintain deque in decreasing order of values.
- Front of deque always contains index of maximum element of current window.

Steps:
1. Remove indices from front if they go out of current window.
2. Remove smaller elements from back (they are useless).
3. Push current index.
4. Once window size reaches k, store nums[dq.front()] as answer.

Time Complexity: O(N)
Space Complexity: O(K)

*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        deque<int> dq;      // stores indices
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            // Remove elements outside window
            if (!dq.empty() && dq.front() == i - k)
                dq.pop_front();
            // Maintain decreasing order in deque
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
          
            dq.push_back(i);
            // Start adding answers once first window is formed
            if (i >= k - 1)
                ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};
