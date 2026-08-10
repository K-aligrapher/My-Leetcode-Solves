class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n=cost.size();
        vector<int>dp(n);

        if(n==1) return cost[0];
        if(n==2) return min(cost[1],cost[0]);
        dp[0]=cost[0];
        dp[1]=cost[1];

        for(int i=2;i<n;i++)
        {
            dp[i]=min(dp[i-1],dp[i-2])+cost[i];
        }
        return min(dp[n-1],dp[n-2]);
    }
};