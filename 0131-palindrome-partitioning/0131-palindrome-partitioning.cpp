class Solution {
public:
    void backtrack(string s,vector<string> &curr, vector<vector<string>> &res, int start)
    {
        if(start == s.size())
        {
        res.push_back(curr);
        return;
        }

        for(int i=start;i<s.size();i++)
        {
          string temp= s.substr(start, i-start+1);
          string rev = temp;
          reverse(rev.begin(),rev.end());
          if(rev==temp)
          {
          curr.push_back(temp);  
          backtrack(s,curr,res,i+1);
          curr.pop_back();
          }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> curr;
        vector<vector<string>> res;

        backtrack(s,curr,res,0);
        return res;
    }
};