#include <vector>
#include <string>

class Solution {
public:
    int minOperations(std::vector<std::string>& logs) {
        int depth = 0;
        
        for (const std::string& log : logs) {
            if (log == "../") {
                if (depth > 0) {
                    depth--;
                }
            } else if (log == "./") {
                continue;
            } else {
                depth++;
            }
        }
        
        return depth;
    }
};
