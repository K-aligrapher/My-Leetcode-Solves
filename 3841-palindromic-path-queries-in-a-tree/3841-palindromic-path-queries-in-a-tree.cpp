#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
private:
    int timer;
    vector<int> in, out, depth;
    vector<vector<int>> up;
    vector<int> bit;
    int LOG;

    // Fenwick Tree (Binary Indexed Tree) for range updates and point queries
    void updateBIT(int idx, int val, int n) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] ^= val;
        }
    }

    void updateRange(int l, int r, int val, int n) {
        updateBIT(l, val, n);
        updateBIT(r + 1, val, n);
    }

    int queryBIT(int idx) {
        int sum_xor = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum_xor ^= bit[idx];
        }
        return sum_xor;
    }

    // DFS to set up Euler Tour and Binary Lifting structures
    void dfs(int u, int p, const vector<vector<int>>& adj, const string& s, int current_mask) {
        in[u] = ++timer;
        current_mask ^= (1 << (s[u] - 'a'));
        
        // Populate initial point values into the BIT structure via differences
        updateRange(in[u], in[u], current_mask, adj.size());

        up[u][0] = (p == -1) ? u : p;
        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u, adj, s, current_mask);
            }
        }
        out[u] = timer;
    }

    // Get Lowest Common Ancestor using Binary Lifting
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        
        for (int i = LOG - 1; i >= 0; --i) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        
        if (u == v) return u;
        
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        timer = 0;
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        
        in.assign(n, 0);
        out.assign(n, 0);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, 0));
        bit.assign(n + 2, 0);

        // Precompute trees
        dfs(0, -1, adj, s, 0);

        // Keep track of active character states dynamically
        string current_s = s;
        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                int old_mask = 1 << (current_s[u] - 'a');
                int new_mask = 1 << (c - 'a');
                int change = old_mask ^ new_mask;

                // Update the subtree range of node u in the flattened tree array
                updateRange(in[u], out[u], change, n);
                current_s[u] = c;
            } 
            else if (type == "query") {
                int u, v;
                ss >> u >> v;

                int lca = getLCA(u, v);
                
                // Fetch dynamic root-to-node path masks from the Fenwick Tree
                int mask_u = queryBIT(in[u]);
                int mask_v = queryBIT(in[v]);
                int mask_lca_char = 1 << (current_s[lca] - 'a');

                int path_mask = mask_u ^ mask_v ^ mask_lca_char;

                // Check if at most one bit is turned on (can form a palindrome)
                ans.push_back(__builtin_popcount(path_mask) <= 1);
            }
        }

        return ans;
    }
};
