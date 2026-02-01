/*
Problem: LeetCode 213 – House Robber II
Link: https://leetcode.com/problems/house-robber-ii/

Approach:
Houses are arranged in a circle, so the first and last houses cannot both be robbed.
We break the problem into two linear cases:
1) Exclude the first house.
2) Exclude the last house.

Time Complexity: O(N)
Space Complexity:
Memoization → O(N)
Tabulation → O(N)
Space Optimized → O(1)
*/

#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////
// MEMOIZATION
//////////////////////////////////////////////////////////////

class Solution {
public:
    long long solve(int i, vector<int>& nums, vector<long long>& dp){
        if(i < 0) return 0;
        if(i == 0) return nums[0];
        if(dp[i] != -1) return dp[i];

        long long take = nums[i];
        if(i > 1) take += solve(i-2, nums, dp);

        long long notTake = solve(i-1, nums, dp);

        return dp[i] = max(take, notTake);
    }

    long long robLinear(vector<int>& nums){
        int n = nums.size();
        vector<long long> dp(n, -1);
        return solve(n-1, nums, dp);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        vector<int> excludeFirst(nums.begin()+1, nums.end());
        vector<int> excludeLast(nums.begin(), nums.end()-1);

        return max(robLinear(excludeFirst), robLinear(excludeLast));
    }
};


//////////////////////////////////////////////////////////////
// TABULATION
//////////////////////////////////////////////////////////////

class Solution {
public:
    long long robLinear(vector<int>& nums){
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];

        vector<long long> dp(n);

        dp[0] = nums[0];

        for(int i = 1; i < n; i++){
            long long take = nums[i];
            if(i > 1) take += dp[i-2];

            long long notTake = dp[i-1];

            dp[i] = max(take, notTake);
        }

        return dp[n-1];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];

        vector<int> excludeFirst(nums.begin()+1, nums.end());
        vector<int> excludeLast(nums.begin(), nums.end()-1);

        return max(robLinear(excludeFirst), robLinear(excludeLast));
    }
};


//////////////////////////////////////////////////////////////
// SPACE OPTIMIZED
//////////////////////////////////////////////////////////////

class Solution {
public:
    long long robLinear(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        long long prev = nums[0], prev2 = 0;

        for (int i = 1; i < n; i++) {
            long long take = nums[i];
            if (i > 1) take += prev2;

            long long notTake = prev;

            long long cur = max(take, notTake);
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> excludeFirst(nums.begin() + 1, nums.end());
        vector<int> excludeLast(nums.begin(), nums.end() - 1);

        return (int)max(robLinear(excludeFirst), robLinear(excludeLast));
    }
};
