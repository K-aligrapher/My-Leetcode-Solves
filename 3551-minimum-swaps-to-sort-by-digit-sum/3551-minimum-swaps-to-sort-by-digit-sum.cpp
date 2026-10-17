class Solution {
private:
    // Pass by value so we can freely modify 'a' without changing the original array
    int sum(int a) 
    {
        int d = 0, k = 0;
        while (a > 0)
        {
            d = a % 10;
            k += d;
            a /= 10; // Fixed: update 'a' instead of 'd' to avoid an infinite loop
        }
        return k;
    }
    
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        
        vector<pair<int, int>> sortedArr(n);
        for (int i = 0; i < n; ++i) {
            sortedArr[i] = {sum(nums[i]), nums[i]};
        }
        
        sort(sortedArr.begin(), sortedArr.end());
        
        unordered_map<int, int> targetIndex;
        for (int i = 0; i < n; ++i) {
            targetIndex[sortedArr[i].second] = i;
        }
        
        vector<bool> visited(n, false);
        int totalSwaps = 0;
        
        for (int i = 0; i < n; ++i) {
            if (visited[i] || targetIndex[nums[i]] == i) {
                continue;
            }
            
            int cycleSize = 0;
            int currentIdx = i;
            
            while (!visited[currentIdx]) {
                visited[currentIdx] = true;
                currentIdx = targetIndex[nums[currentIdx]];
                cycleSize++;
            }
            
            if (cycleSize > 1) {
                totalSwaps += (cycleSize - 1);
            }
        }
        
        return totalSwaps;
    }
};
