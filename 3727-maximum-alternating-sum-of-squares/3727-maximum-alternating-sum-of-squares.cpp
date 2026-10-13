#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        
        vector<long long> squares(n);
        for (int i = 0; i < n; ++i) {
            squares[i] = (long long)nums[i] * nums[i];
        }

        sort(squares.begin(), squares.end());
        
        long long max_score = 0;
        int minus_slots_count = n / 2; 
        
        for (int i = 0; i < n; ++i) {
            if (i < minus_slots_count) {
                max_score -= squares[i];
            } else {
                max_score += squares[i];
            }
        }
        
        return max_score;
    }
};
