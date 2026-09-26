#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // 1. Build a fast lookup hash map from the knowledge base
        unordered_map<string, string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }
        
        string result = "";
        string current_key = "";
        bool inside_bracket = false;
        
        // 2. Parse the string in a single pass
        for (char c : s) {
            if (c == '(') {
                inside_bracket = true;
            } 
            else if (c == ')') {
                inside_bracket = false;
                // Look up the key in the map
                auto it = dict.find(current_key);
                if (it != dict.end()) {
                    result += it->second;
                } else {
                    result += '?';     
                }
                current_key = ""; // Reset for the next bracket pair
            } 
            else {
                // If we are inside brackets, we are building the key name
                if (inside_bracket) {
                    current_key += c;
                } else {
                    result += c;
                }
            }
        }
        
        return result;
    }
};
