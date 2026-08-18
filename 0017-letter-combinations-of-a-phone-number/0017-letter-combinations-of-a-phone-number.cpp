class Solution {
public:
    vector<string> mp = {
        "", "", "abc", "def", "ghi",
        "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(string &digits, vector<string> &res, string &curr, int index)
    {
        if(index == digits.size())
            {
            res.push_back(curr);
            return;
            }
            
        for(char c : mp[digits[index] - '0'])
        {
            curr.push_back(c);
            backtrack(digits, res, curr, index + 1);
            curr.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string curr;

        if(digits.empty())
        return res;

        backtrack(digits,res,curr,0);
        return res;   
    }
};