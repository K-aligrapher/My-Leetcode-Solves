class Solution {
public:
    int countBeautifulPairs(vector<int>& nums) {
       int coprime=0;
       for(int i=0;i<nums.size();i++)
       {
        int k=nums[i];
        while(k>=10) k/=10;

       for(int j=i+1;j<nums.size();j++)
       {
        if(gcd(k,nums[j]%10)==1)
        coprime++;
       } 
       }
       return coprime;
    }
};