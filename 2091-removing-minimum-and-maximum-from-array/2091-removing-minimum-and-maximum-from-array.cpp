#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        int mn = INT_MAX, mx = INT_MIN;
        int mn_i = -1, mx_i = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] < mn) { mn = nums[i]; mn_i = i; }
            if (nums[i] > mx) { mx = nums[i]; mx_i = i; }
        }

        int l = min(mn_i, mx_i);
        int r = max(mn_i, mx_i);

        int a = r + 1;
        int b = n - l;
        int c = (l + 1) + (n - r);

        return min({a, b, c});
    }
};
