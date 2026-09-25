#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> resultSet = parse(expression);
        return vector<string>(resultSet.begin(), resultSet.end());
    }

private:
    set<string> parse(string expr) {
        // Find the first closing brace to resolve the innermost scope first
        size_t j = expr.find('}');
        if (j == string::npos) {
            return {expr}; // Base Case: No braces left, it's just a raw single word
        }

        // Find the corresponding opening brace for this innermost group
        size_t i = expr.rfind('{', j);

        string left = expr.substr(0, i);
        string right = expr.substr(j + 1);
        string middle = expr.substr(i + 1, j - i - 1);

        // Split the items in this isolated innermost group by its commas
        vector<string> options = split(middle, ',');
        set<string> combinedRes;

        // Recombine and recursively parse each variation to let higher levels expand
        for (const string& op : options) {
            set<string> subRes = parse(left + op + right);
            combinedRes.insert(subRes.begin(), subRes.end());
        }

        return combinedRes;
    }

    vector<string> split(const string& s, char delim) {
        vector<string> tokens;
        string token;
        for (char ch : s) {
            if (ch == delim) {
                tokens.push_back(token);
                token.clear();
            } else {
                token += ch;
            }
        }
        tokens.push_back(token);
        return tokens;
    }
};
