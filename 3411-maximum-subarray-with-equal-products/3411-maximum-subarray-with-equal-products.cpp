class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n=nums.size();
        int MAX_LCM=25200;
        int len=0;

        for(int i=0;i<n;i++)
        {
            float prod=1;
            int g_cd=0;
            int l_cm=1;
            for(int j=i;j<n;j++)
            {
                prod*=nums[j];
                if(prod >=MAX_LCM) break;

                g_cd=gcd(g_cd,nums[j]);
                l_cm=lcm(l_cm,nums[j]);

                if(prod==(g_cd*l_cm))
                len=max(len,j-i+1);
            }
        }
        return len;
    }
};