class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const int MAX_XOR=1024;

        vector<vector<bool>> dp(n,vector<bool>(MAX_XOR,false));

        dp[0][grid[0][0]]=true;

        for(int j=1;j<n;j++)
        for(int k=0;k<MAX_XOR;k++)
        {
            if(dp[j-1][k])
            dp[j][k^grid[0][j]]=true;
        }

        for(int i=1;i<m;i++)
        {
            vector<vector<bool>>next_dp(n,vector<bool>(MAX_XOR,false));

            for(int j=0;j<n;j++)
            for(int k=0;k<MAX_XOR;k++)
            {
                if(dp[j][k] || (j>0 && next_dp[j-1][k]))
                next_dp[j][k^grid[i][j]]=true;
            }
            dp=move(next_dp);
        }

        for(int k=0;k<MAX_XOR;k++)
        if(dp[n-1][k])
        return k;

        return -1;
    }
};