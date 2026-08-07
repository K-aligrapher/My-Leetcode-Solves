#include <string>
#include <vector>
#include <algorithm>

class Solution {
private:
    // Helper to extract prime factor counts (2, 3, 5, 7) required by t
    bool getPrimeFactors(long long t, std::vector<int>& factors) {
        std::vector<int> primes = {2, 3, 5, 7};
        for (int i = 0; i < 4; ++i) {
            while (t % primes[i] == 0) {
                factors[i]++;
                t /= primes[i];
            }
        }
        return t == 1; // Returns false if t contains invalid factors like 11, 13 etc.
    }

    // Returns the exact minimum number of single digits needed to satisfy remaining factors
    int getMinDigitsNeeded(const std::vector<int>& factors) {
        int req2 = factors[0], req3 = factors[1], req5 = factors[2], req7 = factors[3];
        int count = req5 + req7 + (req3 / 2) + (req2 / 3);
        int rem3 = req3 % 2;

        if (rem3 == 0) {
            if (req2 % 3 != 0) count += 1;
        } else {
            if (req2 % 3 == 2) count += 2; // Needs both '2' and '6'
            else count += 1;               // Needs either '3' or '6'
        }
        return count;
    }

    // Constructs the smallest possible string suffix given needed factors and required length
    std::string constructSuffix(const std::vector<int>& factors, int length) {
        int req2 = factors[0], req3 = factors[1], req5 = factors[2], req7 = factors[3];
        std::string suffix = "";
        
        while (req5 > 0) { suffix += '5'; req5--; }
        while (req7 > 0) { suffix += '7'; req7--; }
        
        int num9s = req3 / 2;
        int rem3 = req3 % 2;
        
        // Mathematically optimal grouping for combinations of 2 and 3
        if (rem3 == 0) {
            if (req2 % 3 == 1) suffix += '2';
            else if (req2 % 3 == 2) suffix += '4';
        } else {
            if (req2 % 3 == 0) suffix += '3';
            else if (req2 % 3 == 1) suffix += '6';
            else if (req2 % 3 == 2) { suffix += '2'; suffix += '6'; }
        }
        
        int num8s = req2 / 3;
        while (num8s > 0) { suffix += '8'; num8s--; }
        while (num9s > 0) { suffix += '9'; num9s--; }
        
        // Pad with '1's to fill up the target string length container
        while (suffix.length() < length) {
            suffix += '1';
        }
        
        std::sort(suffix.begin(), suffix.end());
        return suffix;
    }

public:
    std::string smallestNumber(std::string num, long long t) {
        std::vector<int> targetFactors(4, 0); 
        if (!getPrimeFactors(t, targetFactors)) {
            return "-1"; 
        }

        int n = num.length();
        std::vector<std::vector<int>> prefixFactors(n + 1, std::vector<int>(4, 0));
        int firstZero = -1;

        // Step 1: Precalculate cumulative prefix factors
        for (int i = 0; i < n; ++i) {
            prefixFactors[i + 1] = prefixFactors[i];
            if (num[i] == '0') {
                if (firstZero == -1) firstZero = i;
            } else {
                int d = num[i] - '0';
                if (d == 2 || d == 6) prefixFactors[i + 1][0]++;
                if (d == 4)           prefixFactors[i + 1][0] += 2;
                if (d == 8)           prefixFactors[i + 1][0] += 3;
                if (d == 3 || d == 6) prefixFactors[i + 1][1]++;
                if (d == 9)           prefixFactors[i + 1][1] += 2;
                if (d == 5)           prefixFactors[i + 1][2]++;
                if (d == 7)           prefixFactors[i + 1][3]++;
            }
        }

        // Step 2: Check if the original string matches without modification
        if (firstZero == -1) {
            bool valid = true;
            for (int j = 0; j < 4; ++j) {
                if (prefixFactors[n][j] < targetFactors[j]) valid = false;
            }
            if (valid) return num;
        }

        // Step 3: Backtrack from right to left to find an increment point
        int limit = (firstZero == -1) ? n - 1 : firstZero;
        for (int i = limit; i >= 0; --i) {
            int startDigit = (num[i] - '0') + 1;
            if (num[i] == '0') startDigit = 1;

            for (int d = startDigit; d <= 9; ++d) {
                std::vector<int> currentFactors = prefixFactors[i];
                
                if (d == 2 || d == 6) currentFactors[0]++;
                if (d == 4)           currentFactors[0] += 2;
                if (d == 8)           currentFactors[0] += 3;
                if (d == 3 || d == 6) currentFactors[1]++;
                if (d == 9)           currentFactors[1] += 2;
                if (d == 5)           currentFactors[2]++;
                if (d == 7)           currentFactors[3]++;

                std::vector<int> rem(4, 0);
                for (int j = 0; j < 4; ++j) {
                    rem[j] = std::max(0, targetFactors[j] - currentFactors[j]);
                }

                int remLength = n - 1 - i;
                if (getMinDigitsNeeded(rem) <= remLength) {
                    std::string ans = num.substr(0, i) + std::to_string(d);
                    ans += constructSuffix(rem, remLength);
                    return ans;
                }
            }
        }

        // Step 4: Scale string length up dynamically if no same-length configuration matches
        int newLength = n + 1;
        while (true) {
            if (getMinDigitsNeeded(targetFactors) <= newLength) {
                return constructSuffix(targetFactors, newLength);
            }
            newLength++;
        }
        return "-1";
    }
};
