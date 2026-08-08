#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();
        
        std::vector<int> suffix(n + 1, 0);
        
        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = suffix[i + 1];
            if (j >= 0 && word1[i] == word2[j]) {
                suffix[i]++;
                j--;
            }
        }
        
        std::vector<int> ans;
        j = 0;
        bool changed = false; 
        
        for (int i = 0; i < n; ++i) {
            if (j == m) break;
            
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } 
            
            else if (!changed) {
                if (suffix[i + 1] >= m - 1 - j) {
                    ans.push_back(i);
                    j++;
                    changed = true; 
                }
            }
        }
        
        return ans.size() == m ? ans : std::vector<int>();
    }
};
