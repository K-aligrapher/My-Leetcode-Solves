class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i=0;i<n;i++)
        nums1[m+i]=nums2[i];

        sort(nums1.begin(),nums1.end());
    }
};

/*
#include <vector>

class Solution {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        int i = m - 1;     // Pointer for valid elements in nums1
        int j = n - 1;     // Pointer for nums2
        int k = m + n - 1; // Pointer for the insertion slot at the back of nums1

        // Compare elements from the back and move the larger one
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } else {
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        // If elements remain in nums2, copy them over
        while (j >= 0) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
        // Note: If elements remain in nums1, they are already in their correct places
    }
};
*/
