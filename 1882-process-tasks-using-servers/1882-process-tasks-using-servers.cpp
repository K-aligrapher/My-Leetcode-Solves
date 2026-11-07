#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        // Elements in idle heap: {weight, index}
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> idle;
        
        // Elements in busy heap: {freeTime, weight, index}
        // Using 'long long' for time to prevent potential integer overflow issues
        using pll = tuple<long long, int, int>;
        priority_queue<pll, vector<pll>, greater<pll>> busy;
        
        // Populate the idle heap with all available servers initially
        for (int i = 0; i < servers.size(); ++i) {
            idle.push({servers[i], i});
        }
        
        int m = tasks.size();
        vector<int> ans(m);
        long long currTime = 0;
        
        for (int j = 0; j < m; ++j) {
            // The task j arrives at least at second j. 
            // The clock cannot run behind the arrival time of the task.
            currTime = max(currTime, (long long)j);
            
            // If all servers are busy, fast-forward time to the earliest completion
            if (idle.empty()) {
                currTime = get<0>(busy.top());
            }
            
            // Release all servers that have finished processing by currTime
            while (!busy.empty() && get<0>(busy.top()) <= currTime) {
                auto [freeTime, w, idx] = busy.top();
                busy.pop();
                idle.push({w, idx});
            }
            
            // Pick the best available server
            auto [w, idx] = idle.top();
            idle.pop();
            
            // Record the assigned server's index for task j
            ans[j] = idx;
            
            // Calculate the new time when this server will become free
            long long nextFreeTime = currTime + tasks[j];
            busy.push({nextFreeTime, w, idx});
        }
        
        return ans;
    }
};
