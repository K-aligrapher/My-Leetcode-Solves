class Solution {
public: 
    void combinationSum3helper(int k, int target, int start, vector<int> &currState, vector<vector<int>> &res)
    {
        if(currState.size()==k)
        {
            if (target == 0) {
                res.push_back(currState);
            }
            return;
        }
        if(target<0)
        return;

        for(int i=start;i<=9;i++)
        {
            currState.push_back(i);
            combinationSum3helper(k,target-i,i+1,currState,res);
            currState.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>currComb;
        vector<vector<int>> res;

        combinationSum3helper(k,n,1,currComb,res);
        return res;
    }
};