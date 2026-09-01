#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& grid, int E) {
        int m = grid.size(), n = grid[0].size(), K = 0;
        int sr = 0, sc = 0, lit[25][25] = {};
        
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 'S') tie(sr, sc) = {i, j};
                else if (grid[i][j] == 'L') lit[i][j] = ++K; // 1-based index

        int target = (1 << K) - 1, moves = 0;
        int start_mask = grid[sr][sc] == 'L' ? (1 << (lit[sr][sc] - 1)) : 0;

        vector<vector<vector<vector<bool>>>> vis(m, vector(n, vector(E + 1, vector<bool>(target + 1))));
        queue<tuple<int, int, int, int>> q; // {r, c, energy, mask}
        
        q.push({sr, sc, E, start_mask});
        vis[sr][sc][E][start_mask] = true;

        int dirs[5] = {-1, 0, 1, 0, -1};

        while (!q.empty()) {
            for (int sz = q.size(); sz > 0; --sz) {
                auto [r, c, e, mask] = q.front(); q.pop();
                if (mask == target) return moves;
                if (e == 0 && grid[r][c] != 'R') continue;

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dirs[i], nc = c + dirs[i+1];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n || grid[nr][nc] == 'X') continue;
                    
                    int ne = (grid[nr][nc] == 'R') ? E : e - 1;
                    int nmask = mask | (grid[nr][nc] == 'L' ? (1 << (lit[nr][nc] - 1)) : 0);

                    if (ne >= 0 && !vis[nr][nc][ne][nmask]) {
                        vis[nr][nc][ne][nmask] = true;
                        q.push({nr, nc, ne, nmask});
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};
