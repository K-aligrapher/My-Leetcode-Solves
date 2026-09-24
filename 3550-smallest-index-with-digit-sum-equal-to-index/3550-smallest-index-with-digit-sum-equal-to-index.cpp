class Solution {
private:
    int sumofD(int n)
    {
        if(n<=9)
        return n;

        int sum=0,d=0;
        while(n>0)
        {
            d=n%10;
            sum+=d;
            n/=10;
        }
        return sum;
    }
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<n;i++)
        {
            if(sumofD(nums[i])==i)
            return i;
        }
        return -1;
    }
};