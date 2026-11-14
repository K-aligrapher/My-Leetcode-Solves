class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n=nums.size();
        int min_sum=INT_MAX;

        for(int i=0;i<n;i++)
        {
            int curr_sum=0;
            for(int j=i;j<n;j++)
            {
                curr_sum+=nums[j];
                int len=j-i+1;

                if(len>=l && len<=r && curr_sum>0)
                min_sum=min(min_sum,curr_sum);

                if(len>r)
                break;
            }
        }
        return min_sum==INT_MAX?-1:min_sum;
    }
};