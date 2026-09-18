#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> leftmost(26, n);
        vector<int> rightmost(26, -1);
        
        // Step 1: Record the boundary indices for each character
        for (int i = 0; i < n; ++i) {
            leftmost[s[i] - 'a'] = min(leftmost[s[i] - 'a'], i);
            rightmost[s[i] - 'a'] = i;
        }
        
        vector<pair<int, int>> validIntervals;
        
        // Step 2: Attempt to generate a valid interval starting at each char's first occurrence
        for (int i = 0; i < 26; ++i) {
            if (leftmost[i] == n) continue; // Character doesn't exist
            
            int start = leftmost[i];
            int end = rightmost[i];
            bool isValid = true;
            
            // Expand the interval if inner characters bleed outside
            for (int j = start; j <= end; ++j) {
                int charIdx = s[j] - 'a';
                
                // If an inner character started before our interval, this setup is invalid
                if (leftmost[charIdx] < start) {
                    isValid = false;
                    break;
                }
                end = max(end, rightmost[charIdx]);
            }
            
            if (isValid) {
                validIntervals.push_back({end, start}); // Store as {end, start} for sorting
            }
        }
        
        // Step 3: Greedy choice (Interval Scheduling)
        sort(validIntervals.begin(), validIntervals.end());
        
        vector<string> result;
        int lastEnd = -1;
        
        for (const auto& interval : validIntervals) {
            int currentEnd = interval.first;
            int currentStart = interval.second;
            
            // If it doesn't overlap with the last chosen interval, take it
            if (currentStart > lastEnd) {
                result.push_back(s.substr(currentStart, currentEnd - currentStart + 1));
                lastEnd = currentEnd;
            }
        }
        
        return result;
    }
};
