#include <string>
#include <algorithm>

class Solution {
public:
    string reversePrefix(string word, char ch) {
        size_t found_idx = word.find(ch);
        if (found_idx != string::npos) {
            reverse(word.begin(), word.begin() + found_idx + 1);
        }
        return word;
    }
};
