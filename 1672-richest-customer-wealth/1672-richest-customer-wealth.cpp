#include <vector>
#include <numeric>   
#include <algorithm> 

class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int ans = 0;

        for (const vector<int>& acc : accounts) {
            int sum = accumulate(acc.begin(), acc.end(), 0);
            ans = max(ans, sum);
        }
        return ans;
    }
};
