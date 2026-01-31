/*
Problem: LeetCode 198 – House Robber
Link: https://leetcode.com/problems/house-robber/

Approach:
We are given an array where each element represents money in a house.
The robber cannot rob two adjacent houses.

At every index, we have two choices:
1) Rob the current house → add nums[i] and move to i-2
2) Skip the current house → move to i-1

So the recurrence becomes:
dp[i] = max(nums[i] + dp[i-2], dp[i-1])

This guarantees maximum profit till index i.

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

int solve(int i, vector<int>& nums, vector<int>& dp) {

    if(i < 0) return 0;
    if(i == 0) return nums[0];

    if(dp[i] != -1) return dp[i];

    int take = nums[i] + solve(i-2, nums, dp);
    int nottake = solve(i-1, nums, dp);

    return dp[i] = max(take, nottake);
}

int robMemo(vector<int>& nums) {

    int n = nums.size();
    vector<int> dp(n, -1);
    return solve(n-1, nums, dp);
}

//////////////////////////////////////////////////////////////
// TABULATION
//////////////////////////////////////////////////////////////

int robTab(vector<int>& nums) {

    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    vector<int> dp(n);

    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for(int i = 2; i < n; i++) {

        int take = nums[i] + dp[i-2];
        int nottake = dp[i-1];

        dp[i] = max(take, nottake);
    }

    return dp[n-1];
}

//////////////////////////////////////////////////////////////
// SPACE OPTIMIZED
//////////////////////////////////////////////////////////////

int rob(vector<int>& nums) {

    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    int prev = nums[0];
    int prev2 = 0;

    for(int i = 1; i < n; i++) {

        int take = nums[i];
        if(i > 1) take += prev2;

        int nottake = prev;

        int cur = max(take, nottake);

        prev2 = prev;
        prev = cur;
    }

    return prev;
}
