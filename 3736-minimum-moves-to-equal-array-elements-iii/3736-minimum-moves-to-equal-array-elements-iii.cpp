class Solution {
public:
    int minMoves(vector<int>& nums) {
        int moves=0;
        int n=nums.size();
        sort(nums.begin(), nums.end());
        int maxi=nums[n-1];

        for(int num : nums)
        moves+=maxi-num;

        return moves;
    }
};