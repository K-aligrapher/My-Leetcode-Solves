#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        vector<vector<int>> dist(n, vector<int>(k + 1, 1e9));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, count] = pq.top();
            pq.pop();

            if (d > dist[u][count]) {
                continue;
            }

            if (u == n - 1) {
                return d;
            }

            for (const auto& [v, w] : adj[u]) {
                int next_count = (labels[u] == labels[v]) ? (count + 1) : 1;

                if (next_count <= k) {
                    if (d + w < dist[v][next_count]) {
                        dist[v][next_count] = d + w;
                        pq.push({dist[v][next_count], v, next_count});
                    }
                }
            }
        }

        int min_dist = 1e9;
        for (int i = 1; i <= k; ++i) {
            min_dist = min(min_dist, dist[n - 1][i]);
        }

        return (min_dist == 1e9) ? -1 : min_dist;
    }
};
