class Solution {
public:
    bool checkDivisibility(int n) {
        int d=0;
        int sum=0;
        int num=n;
        int product=1;
        while(n>0)
        {
            d=n%10;
            sum+=d;
            product*=d;
            n/=10;
        }
        if(num%(sum+product) == 0)
        return true;

        return false;
    }
};