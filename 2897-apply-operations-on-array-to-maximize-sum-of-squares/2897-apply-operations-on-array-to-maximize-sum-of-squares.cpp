#include <vector>
#include <vector>
class Solution 
{public:
    int maxSum(std::vector<int>& nums, int k) {
        long long ans = 0;
        long long mod = 1e9 + 7;
        
        // Count frequencies of set bits at each of the 30 bit positions
        std::vector<int> bitCount(30, 0);
        for (int num : nums) {
            for (int i = 0; i < 30; ++i) {
                if ((num >> i) & 1) {
                    bitCount[i]++;
                }
            }
        }
        
        // Greedily build the k largest numbers
        for (int step = 0; step < k; ++step) {
            long long currentNum = 0;
            for (int i = 0; i < 30; ++i) {
                if (bitCount[i] > 0) {
                    currentNum |= (1LL << i);
                    bitCount[i]--; // Consume one '1' bit for this position
                }
            }
            // Add the square of the constructed number to the answer
            ans = (ans + (currentNum * currentNum) % mod) % mod;
        }
        
        return ans;
    }
};