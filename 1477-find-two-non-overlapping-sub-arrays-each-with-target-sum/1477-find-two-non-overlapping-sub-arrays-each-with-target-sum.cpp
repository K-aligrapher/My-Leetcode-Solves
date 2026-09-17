#include <vector>
#include <algorithm>

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> best(n, 1e9); 
        
        int left = 0;
        int current_sum = 0;
        int min_total_length = 1e9;
        int best_so_far = 1e9; 
        
        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];
            
            while (current_sum > target && left <= right) {
                current_sum -= arr[left];
                left++;
            }
            
            if (current_sum == target) {
                int current_len = right - left + 1;
                
                if (left > 0 && best[left - 1] != 1e9) {
                    min_total_length = std::min(min_total_length, current_len + best[left - 1]);
                }
                
                best_so_far = min(best_so_far, current_len);
            }
            
            best[right] = best_so_far;
        }
        
        return (min_total_length >= 1e9) ? -1 : min_total_length;
    }
};
