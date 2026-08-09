#include <vector>
#include <algorithm>

class Solution {
private:
    std::vector<std::vector<int>> dp;
    std::vector<int> suffixSum;
    int n;

    int solve(int i, int M) {
        if (i >= n) return 0;
        if (i + 2 * M >= n) return suffixSum[i]; // Take all remaining piles
        if (dp[i][M] != -1) return dp[i][M];

        int minOpponentStones = 2e9; // Track the best defensive move

        // Opponent tries to minimize what is left for Alice
        for (int X = 1; X <= 2 * M; ++X) {
            minOpponentStones = std::min(minOpponentStones, solve(i + X, std::max(M, X)));
        }

        // Alice gets the total remaining stones minus what Bob takes
        return dp[i][M] = suffixSum[i] - minOpponentStones;
    }

public:
    int stoneGameII(std::vector<int>& piles) {
        n = piles.size();
        
        // 1. Initialize 2D DP vector directly with -1 (Size: n x n)
        dp.assign(n, std::vector<int>(n + 1, -1));
        suffixSum.resize(n + 1, 0);
        
        // 2. Build suffix sums
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        return solve(0, 1);
    }
};
