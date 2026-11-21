#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> lastSeen(26, -1);

        // DFS to find closest matching ancestors simultaneously
        auto findNewParents = [&](auto& self, int u) -> void {
            int charIdx = s[u] - 'a';
            int prevAncestor = lastSeen[charIdx];

            if (prevAncestor != -1) {
                newParent[u] = prevAncestor;
            }

            lastSeen[charIdx] = u;
            for (int v : adj[u]) {
                self(self, v);
            }
            // Backtrack so sibling branches aren't affected
            lastSeen[charIdx] = prevAncestor;
        };

        findNewParents(findNewParents, 0);

        // Build the modified tree
        vector<vector<int>> newAdj(n);
        for (int i = 1; i < n; ++i) {
            newAdj[newParent[i]].push_back(i);
        }

        // DFS to calculate final subtree sizes
        vector<int> ans(n, 1);
        auto countSizes = [&](auto& self, int u) -> int {
            for (int v : newAdj[u]) {
                ans[u] += self(self, v);
            }
            return ans[u];
        };

        countSizes(countSizes, 0);
        return ans;
    }
};
