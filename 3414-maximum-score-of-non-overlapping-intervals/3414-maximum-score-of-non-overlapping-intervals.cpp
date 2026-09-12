#include <vector>
#include <algorithm>
#include <array>

using namespace std;

// Fixed-size structure to represent a state to avoid heap allocations
struct State {
    long long weight = 0;
    int len = 0;
    array<int, 4> indices = {0, 0, 0, 0};

    // Custom comparator for maximizing weight and breaking ties lexicographically
    bool isBetterThan(const State& other) const {
        if (this->weight != other.weight) {
            return this->weight > other.weight; // Maximize weight
        }
        // Standard lexicographical comparison
        int min_len = min(this->len, other.len);
        for (int i = 0; i < min_len; ++i) {
            if (this->indices[i] != other.indices[i]) {
                return this->indices[i] < other.indices[i];
            }
        }
        return this->len < other.len;
    }
};

struct Interval {
    int start;
    int end;
    int weight;
    int id;

    // Sort primarily by start time to make binary searching forward straightforward
    bool operator<(const Interval& other) const {
        if (this->start != other.start) return this->start < other.start;
        if (this->end != other.end) return this->end < other.end;
        return this->id < other.id;
    }
};

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& input) {
        int n = input.size();
        vector<Interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            intervals[i] = {input[i][0], input[i][1], input[i][2], i};
        }
        
        // 1. Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // 2. Precompute the next non-overlapping interval for every interval using binary search
        vector<int> next_idx(n);
        for (int i = 0; i < n; ++i) {
            Interval target;
            target.start = intervals[i].end + 1; // Strict non-overlapping condition
            
            auto it = lower_bound(intervals.begin() + i + 1, intervals.end(), target,
                                  [](const Interval& a, const Interval& b) {
                                      return a.start < b.start;
                                  });
            next_idx[i] = distance(intervals.begin(), it);
        }

        // 3. Iterative DP Table: dp[i][j] represents best state from interval i with j choices remaining
        // Using n + 1 for base cases (out of bounds)
        vector<vector<State>> dp(n + 1, vector<State>(5));

        // Fill table backwards from the last interval to the first
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j <= 4; ++j) {
                // Option A: Skip the current interval
                State best = dp[i + 1][j];

                // Option B: Take the current interval
                State take;
                take.weight = intervals[i].weight;
                take.len = 1;
                take.indices[0] = intervals[i].id;

                // Append the optimal indices found from the next available non-overlapping state
                State next_state = dp[next_idx[i]][j - 1];
                take.weight += next_state.weight;
                
                for (int k = 0; k < next_state.len; ++k) {
                    take.indices[take.len++] = next_state.indices[k];
                }
                
                // Keep the selected index subset sorted for lexicographical comparison
                sort(take.indices.begin(), take.indices.begin() + take.len);

                // Update the state if taking it provides a strictly better layout
                if (take.isBetterThan(best)) {
                    best = take;
                }

                dp[i][j] = best;
            }
        }

        // 4. Extract and return result from the final state
        State final_state = dp[0][4];
        vector<int> result(final_state.indices.begin(), final_state.indices.begin() + final_state.len);
        return result;
    }
};
