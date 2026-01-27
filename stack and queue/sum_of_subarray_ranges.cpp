/*
 Problem: Sum of Subarray Ranges

 Approach:
 - Use monotonic stacks
 - Compute contribution of every element as maximum and minimum
 - Maintain:
     lmin, rmin → contribution as minimum
     lmax, rmax → contribution as maximum
 - Final answer = totalMax - totalMin

 Time Complexity: O(N)
 Space Complexity: O(N)
*/

class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        vector<long long> lmin(n), rmin(n), lmax(n), rmax(n);
        stack<int> st;
        // Left minimum
        for(int i = 0; i < n; i++) {
            while(!st.empty() && nums[st.top()] > nums[i])
                st.pop();

            if(st.empty())
                lmin[i] = i + 1;
            else
                lmin[i] = i - st.top();

            st.push(i);
        }

        while(!st.empty()) st.pop();

        // Right minimum
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && nums[st.top()] >= nums[i])
                st.pop();

            if(st.empty())
                rmin[i] = n - i;
            else
                rmin[i] = st.top() - i;

            st.push(i);
        }

        while(!st.empty()) st.pop();

        // Left maximum
        for(int i = 0; i < n; i++) {
            while(!st.empty() && nums[st.top()] < nums[i])
                st.pop();

            if(st.empty())
                lmax[i] = i + 1;
            else
                lmax[i] = i - st.top();

            st.push(i);
        }

        while(!st.empty()) st.pop();

        // Right maximum
        for(int i = n - 1; i >= 0; i--) {
            while(!st.empty() && nums[st.top()] <= nums[i])
                st.pop();

            if(st.empty())
                rmax[i] = n - i;
            else
                rmax[i] = st.top() - i;

            st.push(i);
        }

        long long maxSum = 0;
        long long minSum = 0;

        for(int i = 0; i < n; i++) {
            maxSum += nums[i] * lmax[i] * rmax[i];
            minSum += nums[i] * lmin[i] * rmin[i];
        }
        return maxSum - minSum;
    }
};
