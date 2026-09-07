class NumArray {
private:
vector<int>prefix;
public:
    NumArray(vector<int>& nums) {
        prefix.resize(nums.size()+1,0);
        partial_sum(nums.begin(), nums.end(), prefix.begin() + 1);
    }
        
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */