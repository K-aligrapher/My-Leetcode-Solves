class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int sum=0;

        for(int i=0;i<nums.size();i++)
        {
          unordered_set<int> count;
        for(int j=i;j<nums.size();j++)
        {
        count.insert(nums[j]);
        int val=count.size();
        sum+=val*val;
        }
        }
        return sum;
    }
};