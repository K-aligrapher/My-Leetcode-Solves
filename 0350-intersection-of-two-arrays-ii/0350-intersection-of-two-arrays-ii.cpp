class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> count;
        vector<int> res;

        for(int n : nums1)
        count[n]++;

        for(int n : nums2)
        {
            if(count[n]>0)
            {
                res.push_back(n);
                count[n]--;
            }
        }
        return res;
    }
};