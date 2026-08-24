#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix(n);
        
        partial_sum(stones.begin(), stones.end(), prefix.begin());
        
        int max_diff = prefix[n - 1];
        
        for (int i = n - 2; i >= 1; --i) {
            max_diff = max(max_diff, prefix[i] - max_diff);
        }
        
        return max_diff;
    }
};
