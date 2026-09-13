#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> ones1, ones2;
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) ones1.push_back({r, c});
                if (img2[r][c] == 1) ones2.push_back({r, c});
            }
        }
        
        map<pair<int, int>, int> offsetCounts;
        int maxOverlap = 0;
        
        for (const auto& p1 : ones1) {
            for (const auto& p2 : ones2) {
                pair<int, int> vector = {p1.first - p2.first, p1.second - p2.second};
                offsetCounts[vector]++;
                maxOverlap = max(maxOverlap, offsetCounts[vector]);
            }
        }
        
        return maxOverlap;
    }
};
