class Solution {
public:
    int arraySign(vector<int>& nums) {
       long long val=1;
       for(int i=0;i<nums.size();i++)
       val*=nums[i];

       if(val>0) return 1;
       if(val<0) return -1;

       return 0; 
    }
};