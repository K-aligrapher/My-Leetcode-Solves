class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total=accumulate(nums.begin(),nums.end(),0);
        if(total%2 !=0) return false;
        int target=total/2;

        vector<int> dp(target+1,0);
        dp[0]=1;
        for(int num : nums)
        {
            for(int j=target; j>=num; j--)
            if(dp[j-num]) dp[j]=true;
        }
        if(dp[target])
        return true;

        return dp[target];
    }
};