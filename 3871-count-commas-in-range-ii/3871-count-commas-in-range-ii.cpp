class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        for(long long a=1000; a<=n ; a*=1000)
        {
            ans+=(n-a+1);
            if(a>LLONG_MAX/1000) break;
        }
        return ans;
    }
};