#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.length();
        const int INF = 1e9;
        
        vector<vector<int>> cost(n, vector<int>(n, INF));
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_changes = INF;
                
                for (int d = 1; d * d <= len; ++d) {
                    if (len % d == 0) {
                        min_changes = min(min_changes, getChanges(s, i, j, d));
                        if (d != 1 && d * d != len) {
                            min_changes = min(min_changes, getChanges(s, i, j, len / d));
                        }
                    }
                }
                cost[i][j] = min_changes;
            }
        }
    
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0; 
        
        for (int p = 1; p <= k; ++p) {
            for (int i = 2 * p; i <= n; ++i) {
                for (int m = 2 * (p - 1); m <= i - 2; ++m) {
                    if (dp[m][p - 1] != INF) {
                        dp[i][p] = min(dp[i][p], dp[m][p - 1] + cost[m][i - 1]);
                    }
                }
            }
        }
        
        return dp[n][k];
    }

private:
    int getChanges(const string& s, int start, int end, int d) {
        int changes = 0;
        for (int rem = 0; rem < d; ++rem) {
            int left = start + rem;
            int right = end - (d - 1 - rem);
            while (left < right) {
                if (s[left] != s[right]) {
                    changes++;
                }
                left += d;
                right -= d;
            }
        }
        return changes;
    }
};
