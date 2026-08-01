class Solution {
public:
    string makeGood(string s) {
        string k="";
        for(char i : s)
        {
           if(!k.empty() && abs(i - k.back()) == 32)
           k.pop_back();
           else
           k.push_back(i);
        }
        return k;
        
    }
};