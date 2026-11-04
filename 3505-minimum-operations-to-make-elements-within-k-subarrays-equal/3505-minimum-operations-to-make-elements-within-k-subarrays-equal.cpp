#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <climits>

class Solution {
public:
    long long minOperations(std::vector<int>& nums, int x, int k) {
        int n = nums.size();
        
        // Phase 1: Slide a window of size x to find the median-based operation cost for each window.
        // We use two multisets to dynamically find the median and maintain window sums.
        std::multiset<int> lower, upper;
        long long lowerSum = 0, upperSum = 0;
        
        // windowOps[i] will store the minimum operations needed to equalize the subarray nums[i...i+x-1]
        std::vector<long long> windowOps;
        windowOps.reserve(n - x + 1);
        
        for (int i = 0; i < n; ++i) {
            // Insert current element
            if (lower.empty() || nums[i] <= *lower.rbegin()) {
                lower.insert(nums[i]);
                lowerSum += nums[i];
            } else {
                upper.insert(nums[i]);
                upperSum += nums[i];
            }
            
            // Remove the element that slid out of the window
            if (i >= x) {
                int outNum = nums[i - x];
                auto it = lower.find(outNum);
                if (it != lower.end()) {
                    lower.erase(it);
                    lowerSum -= outNum;
                } else {
                    upper.erase(upper.find(outNum));
                    upperSum -= outNum;
                }
            }
            
            // Rebalance the multisets so that 'lower' holds the smaller half (and the median if x is odd)
            if (lower.size() < upper.size()) {
                int val = *upper.begin();
                upper.erase(upper.begin());
                lower.insert(val);
                upperSum -= val;
                lowerSum += val;
            } else if (lower.size() - upper.size() > 1) {
                int val = *lower.rbegin();
                lower.erase(std::prev(lower.end()));
                upper.insert(val);
                lowerSum -= val;
                upperSum += val;
            }
            
            // Once the window is fully formed, calculate L1 cost to equalize elements to the median
            if (i >= x - 1) {
                long long median = *lower.rbegin();
                long long cost = (median * lower.size() - lowerSum) + (upperSum - median * upper.size());
                windowOps.push_back(cost);
            }
        }
        
        // Phase 2: Dynamic Programming to choose k non-overlapping windows
        // dp[i][j] = min operations using first 'i' available elements to pick 'j' windows
        int numWindows = windowOps.size();
        std::vector<std::vector<long long>> dp(numWindows + 1, std::vector<long long>(k + 1, LLONG_MAX / 2));
        
        // Base case: 0 windows picked costs 0 operations
        for (int i = 0; i <= numWindows; ++i) {
            dp[i][0] = 0;
        }
        
        for (int i = 1; i <= numWindows; ++i) {
            for (int j = 1; j <= k; ++j) {
                // Option A: Skip the current window starting at index (i-1)
                dp[i][j] = dp[i - 1][j];
                
                // Option B: Take the current window starting at index (i-1). 
                // The next allowed non-overlapping window can only start after x steps.
                if (i - x >= 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i - x][j - 1] + windowOps[i - 1]);
                } else if (j == 1) {
                    // If it's the very first window picked and we don't have x preceding windows
                    dp[i][j] = std::min(dp[i][j], windowOps[i - 1]);
                }
            }
        }
        
        return dp[numWindows][k];
    }
};