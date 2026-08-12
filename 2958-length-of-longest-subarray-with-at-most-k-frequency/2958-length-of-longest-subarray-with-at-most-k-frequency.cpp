class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        unordered_map<int, int> freq; 
        int l = 0;                    
        int max_len = 0;             

        for(int i = 0; i < n; i++) {
            ans.push_back(nums[i]);
            freq[nums[i]]++;

            while(freq[nums[i]] > k) {
                freq[ans[l]]--;
                l++;
            }

            int current_size = ans.size() - l;
            max_len = max(max_len, current_size);
        }
        return max_len;
    }
};
