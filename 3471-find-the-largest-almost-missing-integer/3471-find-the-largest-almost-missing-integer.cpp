#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int largestInteger(std::vector<int>& nums, int k) {
        int n = nums.size();
        
        if (k == n) {
            return *std::max_element(nums.begin(), nums.end());
        }
        
        std::unordered_map<int, int> counts;
        for (int num : nums) {
            counts[num]++;
        }
        
        if (k == 1) {
            int max_unique = -1;
            for (auto& [num, freq] : counts) {
                if (freq == 1) {
                    max_unique = std::max(max_unique, num);
                }
            }
            return max_unique;
        }
        
        int result = -1;
        if (counts[nums.front()] == 1) result = std::max(result, nums.front());
        if (counts[nums.back()] == 1)  result = std::max(result, nums.back());
        
        return result;
    }
};
