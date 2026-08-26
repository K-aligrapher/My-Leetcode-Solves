#include <string>
#include <algorithm>

class Solution {
public:
    std::string shortestBeautifulSubstring(std::string s, int k) {
        int n = s.length();
        int minLength = n + 1; // Start with an impossible boundary
        std::string ans = "";
        int onesCount = 0;
        int l = 0;

        for (int r = 0; r < n; ++r) {
            if (s[r] == '1') {
                onesCount++;
            }

            // Shrink the window whenever we hit exactly k ones
            while (onesCount == k) {
                int currentLength = r - l + 1;
                std::string currentStr = s.substr(l, currentLength);

                // Scenario 1: We found a strictly shorter beautiful substring
                if (currentLength < minLength) {
                    minLength = currentLength;
                    ans = currentStr;
                } 
                // Scenario 2: Same length, evaluate lexicographical order
                else if (currentLength == minLength) {
                    if (currentStr < ans) {
                        ans = currentStr;
                    }
                }

                // Move left boundary to reduce window width
                if (s[l] == '1') {
                    onesCount--;
                }
                l++;
            }
        }

        return ans;
    }
};
