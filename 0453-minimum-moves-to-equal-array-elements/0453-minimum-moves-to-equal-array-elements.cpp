class Solution {
public:
    int minMoves(vector<int>& nums) {
        long long sum = accumulate(nums.begin(), nums.end(),0LL);
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int min=nums[0];

        return static_cast<int>(sum-(n*min));
    }
};