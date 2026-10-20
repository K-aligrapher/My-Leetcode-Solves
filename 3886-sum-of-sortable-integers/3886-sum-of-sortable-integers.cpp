#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        // Iterate through all possible block sizes k
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue; // k must divide n evenly

            bool valid = true;
            int last_max = INT_MIN;

            // Check every block of size k
            for (int i = 0; i < n; i += k) {
                int drops = 0;
                int min_val = INT_MAX;
                int max_val = INT_MIN;

                // 1. Validate monotonicity and locate drops within the block
                for (int j = 0; j < k; ++j) {
                    int curr = nums[i + j];
                    int next = nums[i + (j + 1) % k]; // Circular next element

                    min_val = std::min(min_val, curr);
                    max_val = std::max(max_val, curr);

                    if (curr > next) {
                        drops++;
                    }
                }

                // If a block has more than 1 drop, it cannot be sorted by rotation
                if (drops > 1) {
                    valid = false;
                    break;
                }

                // Special edge case: If there are duplicates that break the circle rules
                // check if the block can actually be unrolled to a sorted form.
                if (drops == 1) {
                    // Find the single drop index to identify the true minimum and maximum
                    int start_idx = -1;
                    for (int j = 0; j < k; ++j) {
                        if (nums[i + j] > nums[i + (j + 1) % k]) {
                            start_idx = (j + 1) % k;
                            break;
                        }
                    }
                    
                    // Verify that from this minimum point, the sequence is completely non-decreasing
                    int prev = nums[i + start_idx];
                    for (int j = 1; j < k; ++j) {
                        int curr = nums[i + (start_idx + j) % k];
                        if (prev > curr) {
                            valid = false;
                            break;
                        }
                        prev = curr;
                    }
                    
                    if (!valid) break;
                    min_val = nums[i + start_idx];
                    max_val = nums[i + (start_idx + k - 1) % k];
                }

                // 2. Validate inter-block boundary rules
                if (min_val < last_max) {
                    valid = false;
                    break;
                }

                last_max = max_val; // Update the boundary constraint for the next block
            }

            if (valid) {
                ans += k;
            }
        }

        return ans;
    }
};
