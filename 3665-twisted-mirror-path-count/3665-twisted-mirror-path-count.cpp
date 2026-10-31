#include <vector>

using namespace std;

class Solution {
private:
    int MOD = 1e9 + 7;
    int m, n;
    vector<vector<vector<int>>> memo;

    pair<int, int> getReflectedPos(int r, int c, int dir, const vector<vector<int>>& grid) {
        while (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == 1) {
            if (dir == 0) {
                r = r + 1; 
                dir = 1;
            } else {
                c = c + 1;
                dir = 0;
            }
        }
        return {r, c};
    }

    int solve(int r, int c, int dir, const vector<vector<int>>& grid) {
        auto [nextR, nextC] = getReflectedPos(r, c, dir, grid);
        
        if (nextR >= m || nextC >= n) return 0;
        if (nextR == m - 1 && nextC == n - 1) return 1;
        if (memo[nextR][nextC][dir] != -1) return memo[nextR][nextC][dir];

        long long paths = 0;
        paths = (paths + solve(nextR, nextC + 1, 0, grid)) % MOD;
        paths = (paths + solve(nextR + 1, nextC, 1, grid)) % MOD;

        return memo[nextR][nextC][dir] = paths;
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        
        if (m == 1 && n == 1) return grid[0][0] == 0 ? 1 : 0;

        memo.assign(m, vector<vector<int>>(n, vector<int>(2, -1)));

        long long totalPaths = 0;
        totalPaths = (totalPaths + solve(0, 1, 0, grid)) % MOD;
        totalPaths = (totalPaths + solve(1, 0, 1, grid)) % MOD;

        return totalPaths;
    }
};
