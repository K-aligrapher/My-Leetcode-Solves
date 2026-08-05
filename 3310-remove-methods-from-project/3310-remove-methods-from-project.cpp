#include <vector>
#include <numeric>

class Solution {
private:
    void markSuspicious(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& isSuspicious) {
        isSuspicious[u] = true;
        for (int v : adj[u]) {
            if (!isSuspicious[v]) {
                markSuspicious(v, adj, isSuspicious);
            }
        }
    }

public:
    std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations) {
        std::vector<std::vector<int>> adj(n);
        for (const auto& edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        std::vector<bool> isSuspicious(n, false);
        markSuspicious(k, adj, isSuspicious);

        for (const auto& edge : invocations) {
            int u = edge[0];
            int v = edge[1];

            if (!isSuspicious[u] && isSuspicious[v]) {
                std::vector<int> allMethods(n);
                std::iota(allMethods.begin(), allMethods.end(), 0);
                return allMethods; 
            }
        }

        std::vector<int> remaining;
        for (int i = 0; i < n; ++i) {
            if (!isSuspicious[i]) {
                remaining.push_back(i);
            }
        }

        return remaining;
    }
};
