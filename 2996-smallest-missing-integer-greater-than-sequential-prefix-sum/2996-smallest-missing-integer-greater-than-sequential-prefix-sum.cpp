class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n=nums.size();
        int sum=nums[0];

        for(int i=1;i<n;i++)
        {
        if(nums[i]!=nums[i-1]+1)
        break;
        sum+=nums[i];
        }

        unordered_set<int> elements(nums.begin(), nums.end());

        while(elements.count(sum))
        sum++;

        return sum;
    }
};