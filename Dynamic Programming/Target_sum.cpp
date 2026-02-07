/*
Problem: LeetCode 494 – Target Sum

Approach:
1. Let total sum of array be S.
2. Convert problem into counting subsets with sum = (S + target) / 2.
3. If (S + target) is odd or |target| > S, return 0.
4. Now count subsets having this required sum.
5. Use DP where dp[i][j] = number of ways to get sum j using first i elements.
6. Special handling for zeros (they contribute two choices).
7. Tabulation fills dp table bottom-up.

Time Complexity: O(N * K)
Space Complexity: O(N * K)
*/

                                 //MEMOIZATION :
class Solution {
public:
    int countSubsets(int ind, int target, vector<int>& nums, vector<vector<int>>& dp) {
    if (ind == 0) {
        if (target == 0 && nums[0] == 0)
            return 2; // Pick or not pick 0
        if (target == 0 || target == nums[0])
            return 1;
        return 0;
    }
    if (dp[ind][target] != -1)
        return dp[ind][target];
    int notTake = countSubsets(ind - 1, target, nums, dp);
    int take = 0;
    if (nums[ind] <= target)
        take = countSubsets(ind - 1, target - nums[ind], nums, dp);
    return dp[ind][target] = take + notTake;
}
int findTargetSumWays(vector<int>& nums, int target) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if ((totalSum + target) % 2 != 0 || totalSum < abs(target))
        return 0;
    int subsetSum = (totalSum + target) / 2;
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(subsetSum + 1, -1));
    return countSubsets(n - 1, subsetSum, nums, dp);
}
};



                                        //TABULATION :
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);

        if ((totalSum + target) % 2 != 0 || totalSum < abs(target))
            return 0;

        int subsetSum = (totalSum + target) / 2;
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(subsetSum + 1, 0));

        if (nums[0] == 0)
            dp[0][0] = 2;
        else
            dp[0][0] = 1;

        if (nums[0] != 0 && nums[0] <= subsetSum)
            dp[0][nums[0]] = 1;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= subsetSum; ++j) {
                int notTake = dp[i - 1][j];
                int take = 0;
                if (nums[i] <= j)
                    take = dp[i - 1][j - nums[i]];

                dp[i][j] = notTake + take;
            }
        }

        return dp[n - 1][subsetSum];
    }
};
