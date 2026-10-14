class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(num*9<sum)
        return "";

        int nines=sum/9;
        string ans(nines,'9');

        int digit=sum%9;
        if(digit>0)
        ans+= to_string(digit);

        int zeros=num-ans.length();
        ans+=string(zeros,'0');

        return ans;
    }
};