class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n+1,INT_MAX/2);
        dp[0]=0;

        for(int i=1;i<=n;i++)
        {
            int curr=costs[i-1];
            for(int j=max(0,i-3);j<i;j++)
            {
                int jump_length=i-j;
                int total_cost=curr+(jump_length*jump_length);
                dp[i]=min(dp[i],dp[j]+total_cost);
            }
        }
        return dp[n];
    }
};