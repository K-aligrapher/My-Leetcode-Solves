class Solution {public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, int> charMap;
        unordered_map<string, int> wordMap;
        
        int i = 0, n = pattern.length();
        int start = 0, len = s.length();
        
        for (int p_idx = 0; p_idx < n; ++p_idx) {
            // If we ran out of string words before finishing the pattern
            if (start > len) return false;
            
            // Find the boundaries of the current word
            int end = start;
            while (end < len && s[end] != ' ') {
                end++;
            }
            
            // Extract the word using substring pointers
            string word = s.substr(start, end - start);
            char ch = pattern[p_idx];
            
            // Check if the 1-based index tracks match up
            if (charMap[ch] != wordMap[word]) {
                return false;
            }
            
            // Record the current index (+1 to safely treat 0 as "unvisited")
            charMap[ch] = p_idx + 1;
            wordMap[word] = p_idx + 1;
            
            // Move pointer past the space to the next word
            start = end + 1;
        }
        
        // Ensure there are no leftover trailing words in string s
        return start > len;
    }
};