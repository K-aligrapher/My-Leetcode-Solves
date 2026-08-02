#include <iostream>
#include <string>
#include <vector>
#include <numeric>

class Solution {
public:
    int calculate(std::string s) {
        std::vector<int> stack;
        long long current_number = 0; // Prevent overflow during parsing
        char current_sign = '+';
        int n = s.length();

        for (int i = 0; i < n; ++i) {
            char c = s[i];

            // 1. Build the multi-digit number
            if (isdigit(c)) {
                current_number = current_number * 10 + (c - '0');
            }

            // 2. Process operators or evaluate at the end of the string
            // Skip spaces unless it's the last character of the expression
            if ((!isdigit(c) && !isspace(c)) || i == n - 1) {
                if (current_sign == '+') {
                    stack.push_back(current_number);
                } 
                else if (current_sign == '-') {
                    stack.push_back(-current_number);
                } 
                else if (current_sign == '*') {
                    int top = stack.back();
                    stack.pop_back();
                    stack.push_back(top * current_number);
                } 
                else if (current_sign == '/') {
                    int top = stack.back();
                    stack.pop_back();
                    stack.push_back(top / current_number);
                }
                
                // Track the next operator and reset number
                current_sign = c;
                current_number = 0;
            }
        }

        // 3. Accumulate all elements in the stack
        int result = 0;
        for (int val : stack) {
            result += val;
        }

        return result;
    }
};
