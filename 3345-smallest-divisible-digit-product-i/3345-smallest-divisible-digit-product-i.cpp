class Solution {
public:
    int prod(int k)
    {
        int d,p=1;
        while(k>0)
        {
          d=k%10;
          p*=d;
          k/=10;
        }
        return p;
    }
    int smallestNumber(int n, int t) {
        int i=n;
        if((prod(i)%t) == 0)
        return i;
        else
        return smallestNumber(i+1,t);
    }
};