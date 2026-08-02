class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        // dp[i][j] stores the maximum relative score the current player can get from piles[i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: Only one pile left
        for (int i = 0; i < n; i++) {
            dp[i][i] = piles[i];
        }
        
        // Build the DP table for intervals of increasing length
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                // Current player chooses either the left pile or the right pile
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        
        // If Alice's relative score for the whole array is greater than 0, she wins
        return dp[0][n - 1] > 0;
    }
};
