class Solution {
public:
    using ll = long long;

    ll gcd(ll a, ll b) {
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto count = [&](ll x) {
            ll res = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                ll cur = 1;
                bool overflow = false;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        cur = lcm(cur, (ll)coins[i]);
                        if (cur > x) {
                            overflow = true;
                            break;
                        }
                    }
                }

                if (overflow) continue;

                if (__builtin_popcount(mask) & 1)
                    res += x / cur;
                else
                    res -= x / cur;
            }

            return res;
        };

        ll lo = 1;
        ll hi = 1e18;

        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;

            if (count(mid) >= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        return lo;
    }
};