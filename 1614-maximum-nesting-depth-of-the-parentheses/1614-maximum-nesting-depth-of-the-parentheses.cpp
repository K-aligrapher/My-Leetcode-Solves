class Solution {
public:
    int maxDepth(string s) {
    int maxdepth=0;
    int currdepth=0;

    for(char c : s)
    {
        if(c=='(')
        {
        currdepth++;
        maxdepth=max(maxdepth,currdepth);
        }
        else if(c==')')
        currdepth--;
    }    
    return maxdepth;
    }
};