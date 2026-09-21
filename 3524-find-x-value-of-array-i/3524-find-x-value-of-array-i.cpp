#include <vector>

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (const int num : nums) {
            vector<long long> newDp(k, 0);
            int numMod = num % k;

            // Case 1: Start a brand new subarray consisting only of `num`
            newDp[numMod] = 1;

            // Case 2: Extend all valid subarrays that ended at the previous position
            for (int i = 0; i < k; ++i) {
                if (dp[i] > 0) {
                    int newMod = (static_cast<long long>(i) * numMod) % k;
                    newDp[newMod] += dp[i];
                }
            }

            // Accumulate the current step counts into the final answer array
            for (int i = 0; i < k; ++i) {
                ans[i] += newDp[i];
            }

            // Move the current state to the DP array for the next iteration
            dp = move(newDp);
        }

        return ans;
    }
};
