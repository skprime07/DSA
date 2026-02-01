/*
Problem: LeetCode 1814 – Count Nice Pairs in an Array

Approach:
A pair (i, j) is nice if:
nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])

Rearranging gives:
nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])

So for every number, we compute:
key = x - reverse(x)

Now the problem becomes counting pairs with equal keys.
We use a hashmap to store frequency of each key. For every new element,
all previous elements with the same key form valid pairs, so we add the
current frequency to the answer and then increment the count.

Modulo is applied since the answer can be large.

Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution {
public:

    int rev(int x) {
        int r = 0;
        while(x) {
            r = r * 10 + (x % 10);
            x /= 10;
        }
        return r;
    }

    int countNicePairs(vector<int>& nums) {

        const int MOD = 1e9 + 7;
        unordered_map<int,long long> mp;
        long long ans = 0;

        for(int x : nums) {

            int key = x - rev(x);

            ans = (ans + mp[key]) % MOD;
            mp[key]++;
        }

        return ans;
    }
};
