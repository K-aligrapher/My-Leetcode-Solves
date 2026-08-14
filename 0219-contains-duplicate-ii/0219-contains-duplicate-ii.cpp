class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        bool ans = false;
        unordered_map<int,int>num_to_index;
        for(int i=0;i<nums.size();i++)
        {
            if (num_to_index.find(nums[i]) != num_to_index.end()) 
            {
                if(i-num_to_index[nums[i]]<=k)
                ans=true;
            }
            num_to_index[nums[i]]=i;
        }
        return ans;
    }
};