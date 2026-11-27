#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        vector<int> dp(budget + 1, 0);
        int min_price = INT_MAX;

        for (const auto& item : items) {
            int factor = item[0];
            int price = item[1];
            min_price = min(min_price, price);

            int gain = 0;
            for (const auto& other : items) {
                if (other[0] % factor == 0) {
                    gain++;
                }
            }

            for (int b = budget; b >= price; --b) {
                dp[b] = max(dp[b], dp[b - price] + gain);
            }
        }

        int max_items = 0;
        for (int b = 0; b <= budget; ++b) {
            max_items = max(max_items, dp[b] + (budget - b) / min_price);
        }

        return max_items;
    }
};
