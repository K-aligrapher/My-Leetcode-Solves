#include <vector>

class Solution {
private:
    int rows, cols;

    void sinkIsland(vector<vector<int>>& grid, int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 1) {
            return;
        }

        grid[r][c] = 1;

        sinkIsland(grid, r + 1, c); 
        sinkIsland(grid, r - 1, c);
        sinkIsland(grid, r, c + 1); 
        sinkIsland(grid, r, c - 1);
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        int closedIslandsCount = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && grid[r][c] == 0) {
                    sinkIsland(grid, r, c);
                }
            }
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0) {
                    closedIslandsCount++;
                    sinkIsland(grid, r, c); 
                }
            }
        }

        return closedIslandsCount;
    }
};
