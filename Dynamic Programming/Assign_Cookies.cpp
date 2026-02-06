/*
Problem: LeetCode 455 – Assign Cookies

Approach:
1. Sort both greed factors and cookie sizes.
2. Use two pointers: one for cookies, one for children.
3. Try to satisfy smallest greedy child with smallest available cookie.
4. If cookie size >= greed, assign it and move both pointers.
5. Otherwise move cookie pointer.
6. Count how many children are satisfied.

Time Complexity: O(N log N)
Space Complexity: O(1)
*/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int left = 0, right = 0;

        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        while(left < s.size() && right < g.size()){
            if(g[right] <= s[left]){
                right++;
            }
            left++;
        }

        return right;
    }
};
