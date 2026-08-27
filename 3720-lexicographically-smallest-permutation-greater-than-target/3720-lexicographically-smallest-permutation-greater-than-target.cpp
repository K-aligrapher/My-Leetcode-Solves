#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
    
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        string prefix = "";
        int match_len = 0;
        
        vector<int> temp_count = count;
        while (match_len < n && temp_count[target[match_len] - 'a'] > 0) {
            temp_count[target[match_len] - 'a']--;
            match_len++;
        }
    
        for (int i = match_len; i >= 0; i--) {
            vector<int> current_avail = count;
            for (int j = 0; j < i; j++) {
                current_avail[target[j] - 'a']--;
            }
            
            if (i == n) continue; 
            
            char target_char = target[i];
            bool found_breakpoint = false;
            char replacement_char = ' ';
            
            for (int c = (target_char - 'a') + 1; c < 26; c++) {
                if (current_avail[c] > 0) {
                    replacement_char = 'a' + c;
                    current_avail[c]--; 
                    found_breakpoint = true;
                    break;
                }
            }
            
            if (found_breakpoint) {
                string result = target.substr(0, i); 
                result += replacement_char;              
                
                for (int c = 0; c < 26; c++) {
                    while (current_avail[c] > 0) {
                        result += ('a' + c);
                        current_avail[c]--;
                    }
                }
                return result;
            }
        }
        
        return ""; 
    }
};
