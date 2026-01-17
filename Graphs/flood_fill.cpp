/*
 Problem: Flood Fill

 Approach:
 - Use Depth First Search (DFS) starting from (sr, sc)
 - Replace all connected pixels having the initial color with the new color
 - Traverse in 4 directions (up, right, down, left)

 Time Complexity: O(N * M)
 Space Complexity: O(N * M)   // recursion stack in worst case
*/

class Solution {
private:
    void dfs(int row, int col,
             vector<vector<int>> &image,
             int newColor, int initialColor,
             int delRow[], int delCol[]) {

        image[row][col] = newColor;
        int n = image.size();
        int m = image[0].size();

        for (int i = 0; i < 4; i++) {
            int newRow = row + delRow[i];
            int newCol = col + delCol[i];

            if (newRow >= 0 && newRow < n &&
                newCol >= 0 && newCol < m &&
                image[newRow][newCol] == initialColor) {

                dfs(newRow, newCol, image, newColor, initialColor, delRow, delCol);
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr, int sc, int newColor) {

        int initialColor = image[sr][sc];

        // If the new color is same as initial, no change needed
        if (initialColor == newColor)
            return image;

        int delRow[4] = {-1, 0, 1, 0};
        int delCol[4] = {0, 1, 0, -1};

        dfs(sr, sc, image, newColor, initialColor, delRow, delCol);

        return image;
    }
};
