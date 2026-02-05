/*
Problem: Count Partitions With Given Difference (Coding Ninjas / GFG)

Approach:
1. Let total sum of array be S.
2. Convert problem into counting subsets with sum = (S + d) / 2.
3. If (S + d) is odd or S < d, answer is 0.
4. Use DP where dp[i][t] stores number of ways to form sum t using first i elements.
5. Handle zero carefully (it contributes two choices).
6. Memoization uses recursion + dp table.
7. Tabulation builds dp iteratively.
8. Space optimized version keeps only previous row.

Time Complexity: O(N * K)
Space Complexity:
Memoization → O(N * K)
Tabulation → O(N * K)
Space Optimized → O(K)
*/

                             //MEMOIZATION :
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int f(int i, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if (i == 0) {
        if (target == 0 && arr[0]==0) return 2;
        if (target == 0 || target == arr[0]) return 1;
        return 0;
    }
    if (dp[i][target] != -1) return dp[i][target];
    int notTake = f(i-1, target, arr, dp);
    int take = 0;
    if (arr[i] <= target) take = f(i-1, target-arr[i], arr, dp);
    return dp[i][target] = (notTake + take) % mod;
}

int countPartitions(int n, int d, vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if ((sum + d) % 2 != 0 || sum < d) return 0;
    int target = (sum + d)/2;
    vector<vector<int>> dp(n, vector<int>(target+1, -1));
    return f(n-1, target, arr, dp);
}



                                 //TABULATION :      
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int countPartitions(int n, int d, vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if ((sum + d) % 2 != 0 || sum < d) return 0;
    int target = (sum + d)/2;
    vector<vector<int>> dp(n, vector<int>(target+1,0));

    if (arr[0]==0) dp[0][0]=2;
    else dp[0][0]=1;
    if (arr[0]!=0 && arr[0]<=target) dp[0][arr[0]]=1;

    for(int i=1;i<n;i++) {
        for(int t=0;t<=target;t++) {
            int notTake=dp[i-1][t];
            int take=0;
            if (arr[i]<=t) take=dp[i-1][t-arr[i]];
            dp[i][t]=(notTake+take)%mod;
        }
    }
    return dp[n-1][target];
}


                                //SPACE OPTIMISED:
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int countPartitions(int n, int d, vector<int> &arr) {
    int sum = accumulate(arr.begin(), arr.end(), 0);
    if ((sum + d) % 2 != 0 || sum < d) return 0;
    int target = (sum + d)/2;
    vector<int> prev(target+1,0);

    if (arr[0]==0) prev[0]=2;
    else prev[0]=1;
    if (arr[0]!=0 && arr[0]<=target) prev[arr[0]]=1;

    for(int i=1;i<n;i++) {
        vector<int> cur(target+1,0);
        for(int t=0;t<=target;t++) {
            int notTake=prev[t];
            int take=0;
            if (arr[i]<=t) take=prev[t-arr[i]];
            cur[t]=(notTake+take)%mod;
        }
        prev=cur;
    }
    return prev[target];
}
