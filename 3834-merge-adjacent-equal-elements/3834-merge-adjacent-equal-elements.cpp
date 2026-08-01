#include <vector>

class Solution {
public:
    std::vector<long long> mergeAdjacent(std::vector<int>& nums) {
        std::vector<long long> ans;
        
        for (int i : nums) {
            long long current = i;
            
            while (!ans.empty() && ans.back() == current) {
                ans.pop_back(); 
                current *= 2;  
            }
            
            ans.push_back(current);
        }
        
        return ans; 
    }
};
