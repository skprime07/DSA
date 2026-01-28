/*
Problem: LeetCode 84 – Largest Rectangle in Histogram

Approach:
- Use a Monotonic Increasing Stack (store indices).
- Add a 0 at the end to force calculation of remaining bars.
- Traverse the heights:
    - While current height is smaller than stack top:
        → Pop index
        → Calculate rectangle area using popped height
        → Width = current index - previous smaller index - 1
    - Push current index into stack.
- Track maximum area.

Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        int ret = 0;
        // Push 0 to process all remaining bars
        height.push_back(0);
        // Stack to store indices (monotonic increasing)
        vector<int> index;
        for(int i = 0; i < height.size(); i++) {
            // Calculate area while current bar is smaller
            while(index.size() > 0 && height[index.back()] >= height[i]) {
                int h = height[index.back()];   // height of rectangle
                index.pop_back();
                // Previous smaller index
                int sidx = index.size() > 0 ? index.back() : -1;
                // Width = current index - previous smaller - 1
                ret = max(ret, h * (i - sidx - 1));
            }
            // Push current index
            index.push_back(i);
        }
        return ret;
    }
};
