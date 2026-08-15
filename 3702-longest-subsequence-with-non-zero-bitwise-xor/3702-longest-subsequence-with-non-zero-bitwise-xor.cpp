class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int total_xor=0;
        bool has_nonzero=false;

        for(int n : nums)
        {
            total_xor ^= n;
            if(n!=0)
            has_nonzero=true;
        }
        if(total_xor!=0)
        return nums.size();

        return has_nonzero? nums.size()-1 : 0;
    }
};