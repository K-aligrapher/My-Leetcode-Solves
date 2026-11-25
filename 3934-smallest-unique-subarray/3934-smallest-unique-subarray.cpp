class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int l = 1, r = nums.size(), ans = r;
        
        auto ok = [&](int L) {
            uint64_t h = 0, p = 1, B = 1315423911ULL;
            for (int i = 0; i < L - 1; ++i) p *= B;
            
            unordered_map<uint64_t, int> cnt;
            for (int i = 0; i < nums.size(); ++i) {
                if (i >= L) h -= (nums[i - L] + 1ULL) * p;
                h = h * B + (nums[i] + 1ULL);
                if (i >= L - 1) cnt[h]++;
            }
            for (auto& [k, v] : cnt) if (v == 1) return true;
            return false;
        };

        while (l <= r) {
            int m = (l + r) / 2;
            ok(m) ? (ans = m, r = m - 1) : (l = m + 1);
        }
        return ans;
    }
};
