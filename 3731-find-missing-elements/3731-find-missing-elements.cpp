class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        if (nums.empty()) return {};
        
        sort(nums.begin(), nums.end());
        vector<int> ans;
        
        int n = nums.back();
        int idx = 0; 
        
        for (int i = nums[0]; i <= n; i++) {
            if (idx < nums.size() && nums[idx] == i) {
                while (idx < nums.size() && nums[idx] == i) {
                    idx++;
                }
            } else {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
