#include <vector>

class Solution {
private:
    long long MOD = 1e9 + 7;
    std::vector<std::vector<long long>> table;

    // Precompute Pascal's Triangle for combinations nCr
    void generatePascalTriangle(int n) {
        table.assign(n + 1, std::vector<long long>(n + 1, 1));
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }
    }

    long long calculateWays(const std::vector<int>& nums) {
        if (nums.size() <= 2) return 1; // Base case: 0, 1, or 2 elements have only 1 way

        int root = nums[0];
        std::vector<int> left, right;

        // Partition elements into left and right subtrees
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        int totalSlots = left.size() + right.size();
        long long combinations = table[totalSlots][left.size()];

        // Recurse down both subtrees
        long long leftWays = calculateWays(left);
        long long rightWays = calculateWays(right);

        // Combine using modulo arithmetic
        return (((combinations * leftWays) % MOD) * rightWays) % MOD;
    }

public:
    int numOfWays(std::vector<int>& nums) {
        int n = nums.size();
        generatePascalTriangle(n);
        
        // Subtract 1 to exclude the original arrangement
        // Add MOD before taking modulo to handle potential negative values in C++
        return (calculateWays(nums) - 1 + MOD) % MOD;
    }
};
