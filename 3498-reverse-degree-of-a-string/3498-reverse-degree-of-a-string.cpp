class Solution {
public:
    int reverseDegree(string s) {
        int sum=0;
        int idx=1;
        for(char c : s)
        {
            int revpos= 26 -(c-'a');
            sum+= idx*revpos;
            idx++;
        }
        return sum;
    }
};