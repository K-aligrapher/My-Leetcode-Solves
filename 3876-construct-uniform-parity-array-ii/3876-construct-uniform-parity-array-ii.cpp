#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1) {
        int min_odd = INT_MAX;
        
        for (int x : nums1) {
            if (x % 2 != 0) { 
                min_odd = min(min_odd, x);
            }
        }
        
        if (min_odd == INT_MAX) {
            return true;
        }
        
        for (int x : nums1) {
            if (x % 2 == 0 && x < min_odd) {
                return false;
            }
        }
        
        return true;
    }
};
