#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    long long mod = 1e9 + 7;
    vector<long long> sum1, sum2, lazy;

    void push(int node, int start, int end) {
        if (lazy[node] == 0) return;
        int mid = (start + end) / 2;
        int left = 2 * node, right = 2 * node + 1;
        long long val = lazy[node];

        sum2[left] = (sum2[left] + 2 * val * sum1[left] % mod + (mid - start + 1) * val % mod * val % mod) % mod;
        sum1[left] = (sum1[left] + (mid - start + 1) * val) % mod;
        lazy[left] = (lazy[left] + val) % mod;

        sum2[right] = (sum2[right] + 2 * val * sum1[right] % mod + (end - mid) * val % mod * val % mod) % mod;
        sum1[right] = (sum1[right] + (end - mid) * val) % mod;
        lazy[right] = (lazy[right] + val) % mod;

        lazy[node] = 0;
    }

    void update(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            sum2[node] = (sum2[node] + 2 * sum1[node] + (end - start + 1)) % mod;
            sum1[node] = (sum1[node] + (end - start + 1)) % mod;
            lazy[node] = (lazy[node] + 1) % mod;
            return;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r);
        update(2 * node + 1, mid + 1, end, l, r);
        sum1[node] = (sum1[2 * node] + sum1[2 * node + 1]) % mod;
        sum2[node] = (sum2[2 * node] + sum2[2 * node + 1]) % mod;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sum1.assign(4 * n, 0);
        sum2.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        unordered_map<int, int> last_pos;
        long long total_sum = 0;

        for (int i = 0; i < n; ++i) {
            int last = last_pos.count(nums[i]) ? last_pos[nums[i]] : -1;
            update(1, 0, n - 1, last + 1, i);
            total_sum = (total_sum + sum2[1]) % mod;
            last_pos[nums[i]] = i;
        }

        return total_sum;
    }
};
