#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Solution {
private:
    std::vector<std::string> result;

    bool isValid(const std::string& str) {
        int count = 0;
        for (char c : str) {
            if (c == '(') count++;
            else if (c == ')') {
                count--;
                if (count < 0) return false;
            }
        }
        return count == 0;
    }

    void dfs(std::string s, int start, int remL, int remR) {
        // Base case: No more removals needed
        if (remL == 0 && remR == 0) {
            if (isValid(s)) {
                result.push_back(s);
            }
            return;
        }

        for (int i = start; i < s.length(); i++) {
            // Optimization: Skip consecutive identical characters to prevent duplicate states
            if (i > start && s[i] == s[i - 1]) continue;

            // Try removing an unmatched closing parenthesis
            if (remR > 0 && s[i] == ')') {
                dfs(s.substr(0, i) + s.substr(i + 1), i, remL, remR - 1);
            }
            // Try removing an unmatched opening parenthesis
            else if (remL > 0 && s[i] == '(') {
                dfs(s.substr(0, i) + s.substr(i + 1), i, remL - 1, remR);
            }
        }
    }

public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        int remL = 0, remR = 0;

        // Calculate the exact amount of '(' and ')' that are breaking validity
        for (char c : s) {
            if (c == '(') {
                remL++;
            } else if (c == ')') {
                if (remL > 0) remL--; // Matches a previous '('
                else remR++;          // Unmatched ')'
            }
        }

        dfs(s, 0, remL, remR);
        return result;
    }
};
