#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingMultiple(std::vector<int>& nums, int k) {
        unordered_set<int> seen(nums.begin(), nums.end());
        
        int current_multiple = k;
        
        while (seen.count(current_multiple)) {
            current_multiple += k;
        }
        
        return current_multiple;
    }
};
