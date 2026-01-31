/*
Problem: Frog Jump 

Time Complexity (all): O(N)
Space:
Memoization → O(N)
Tabulation → O(N)
Space Optimized → O(1)
*/

#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////
// 1️ MEMOIZATION (Top-Down)
//////////////////////////////////////////////////////////////

int solve(int ind, vector<int>& heights, vector<int>& dp) {

    if (ind == 0) return 0;

    if (dp[ind] != -1) return dp[ind];

    int left = solve(ind - 1, heights, dp) +
               abs(heights[ind] - heights[ind - 1]);

    int right = INT_MAX;
    if (ind > 1)
        right = solve(ind - 2, heights, dp) +
                abs(heights[ind] - heights[ind - 2]);

    return dp[ind] = min(left, right);
}

int frogJumpMemo(int n, vector<int>& heights) {

    vector<int> dp(n, -1);
    return solve(n - 1, heights, dp);
}

//////////////////////////////////////////////////////////////
// 2️ TABULATION (Bottom-Up)
//////////////////////////////////////////////////////////////

int frogJumpTab(int n, vector<int>& heights) {

    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {

        int fs = dp[i - 1] + abs(heights[i] - heights[i - 1]);

        int ss = INT_MAX;
        if (i > 1)
            ss = dp[i - 2] + abs(heights[i] - heights[i - 2]);

        dp[i] = min(fs, ss);
    }

    return dp[n - 1];
}

//////////////////////////////////////////////////////////////
// 3️ SPACE OPTIMIZED
//////////////////////////////////////////////////////////////

int frogJump(int n, vector<int>& heights) {

    int prev = 0;   // dp[i-1]
    int prev2 = 0;  // dp[i-2]

    for (int i = 1; i < n; i++) {

        int fs = prev + abs(heights[i] - heights[i - 1]);

        int ss = INT_MAX;
        if (i > 1)
            ss = prev2 + abs(heights[i] - heights[i - 2]);

        int cur = min(fs, ss);

        prev2 = prev;
        prev = cur;
    }

    return prev;
}
