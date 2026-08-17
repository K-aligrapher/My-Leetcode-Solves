#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    int memo[501][501];

    int solve(int i, int j, const std::vector<int>& prefSum) {
        if (i == j) return 0;
        if (memo[i][j] != -1) return memo[i][j];

        int maxScore = 0;

        for (int k = i; k < j; ++k) {
            int leftSum = prefSum[k + 1] - prefSum[i];
            int rightSum = prefSum[j + 1] - prefSum[k + 1];

            if (leftSum < rightSum) {
                maxScore = std::max(maxScore, leftSum + solve(i, k, prefSum));
            } 
            else if (leftSum > rightSum) {
                maxScore = std::max(maxScore, rightSum + solve(k + 1, j, prefSum));
            } 
            else {
                int chooseLeft = leftSum + solve(i, k, prefSum);
                int chooseRight = rightSum + solve(k + 1, j, prefSum);
                maxScore = std::max({maxScore, chooseLeft, chooseRight});
            }
        }

        return memo[i][j] = maxScore;
    }

public:
    int stoneGameV(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        std::fill(&memo[0][0], &memo[0][0] + sizeof(memo) / sizeof(int), -1);

        std::vector<int> prefSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefSum[i + 1] = prefSum[i] + stoneValue[i];
        }

        return solve(0, n - 1, prefSum);
    }
};
