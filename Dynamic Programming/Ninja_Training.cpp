/*
Problem: Ninja Training 

Approach:
1. On each day, choose a task different from previous day.
2. Use DP where dp[day][last] = max points till this day if last task was 'last'.
3. Try all 3 tasks except 'last' and take maximum.
4. Final answer is dp[n-1][3] (3 means no restriction on last task).

Time Complexity: O(N * 4 * 3)
Space Complexity:
Memoization → O(N * 4)
Tabulation → O(N * 4)
Space Optimized → O(4)
*/

#include <bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////
// MEMOIZATION
//////////////////////////////////////////////////////////////

int f(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp) {

    if(dp[day][last] != -1) return dp[day][last];

    if(day == 0){
        int maxi = 0;
        for(int task = 0; task < 3; task++){
            if(task != last)
                maxi = max(maxi, points[0][task]);
        }
        return dp[day][last] = maxi;
    }

    int maxi = 0;
    for(int task = 0; task < 3; task++){
        if(task != last){
            int val = points[day][task] + f(day-1, task, points, dp);
            maxi = max(maxi, val);
        }
    }

    return dp[day][last] = maxi;
}

int ninjaTrainingMemo(int n, vector<vector<int>> &points) {

    vector<vector<int>> dp(n, vector<int>(4, -1));
    return f(n-1, 3, points, dp);
}

//////////////////////////////////////////////////////////////
// TABULATION
//////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

int ninjaTraining(int n, vector<vector<int>>& points) {

    // dp[day][last] = max points till 'day' if last task was 'last'
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // Base case: day = 0
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max({points[0][0], points[0][1], points[0][2]});

    // Fill dp table
    for(int day = 1; day < n; day++) {
        for(int last = 0; last < 4; last++) {

            dp[day][last] = 0;

            for(int task = 0; task < 3; task++) {
                if(task != last) {
                    int activity = points[day][task] + dp[day - 1][task];
                    dp[day][last] = max(dp[day][last], activity);
                }
            }
        }
    }

    return dp[n - 1][3];
}


//////////////////////////////////////////////////////////////
// SPACE OPTIMIZED
//////////////////////////////////////////////////////////////

int ninjaTraining(int n, vector<vector<int>>& points) {

    vector<int> prev(4,0);

    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max({points[0][0], points[0][1], points[0][2]});

    for(int day = 1; day < n; day++) {

        vector<int> curr(4,0);

        for(int last = 0; last < 4; last++) {
            for(int task = 0; task < 3; task++) {
                if(task != last) {
                    curr[last] = max(curr[last],
                        points[day][task] + prev[task]);
                }
            }
        }
        prev = curr;
    }

    return prev[3];
}
