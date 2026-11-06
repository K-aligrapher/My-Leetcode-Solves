#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int num_queries = queries.size();
        vector<int> ans(num_queries);
        
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1]; 
        });
        
        vector<pair<int, int>> sorted_queries(num_queries);
        for (int i = 0; i < num_queries; ++i) {
            sorted_queries[i] = {queries[i], i};
        }
        sort(sorted_queries.begin(), sorted_queries.end());
        
        vector<int> server_counts(n + 1, 0); 
        int unique_active = 0;
        
        int left = 0;
        int right = 0;
        int total_logs = logs.size();
        
        for (const auto& [query_time, original_idx] : sorted_queries) {
            int start_time = query_time - x;
            int end_time = query_time;
            
            while (right < total_logs && logs[right][1] <= end_time) {
                int server_id = logs[right][0];
                if (server_counts[server_id] == 0) {
                    unique_active++;
                }
                server_counts[server_id]++;
                right++;
            }
            
            while (left < total_logs && logs[left][1] < start_time) {
                int server_id = logs[left][0];
                server_counts[server_id]--;
                if (server_counts[server_id] == 0) {
                    unique_active--;
                }
                left++;
            }
            
            ans[original_idx] = n - unique_active;
        }
        
        return ans;
    }
};
