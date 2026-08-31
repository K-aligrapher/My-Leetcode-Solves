#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int minDistance = INT_MAX;
        int firstCriticalIndex = -1;
        int prevCriticalIndex = -1;
        
        int currentIndex = 1; 
        ListNode* prevNode = head;
        ListNode* currNode = head->next;

        while (currNode->next != nullptr) {
            ListNode* nextNode = currNode->next;

            bool isLocalMaxima = (currNode->val > prevNode->val) && (currNode->val > nextNode->val);
            bool isLocalMinima = (currNode->val < prevNode->val) && (currNode->val < nextNode->val);

            if (isLocalMaxima || isLocalMinima) {
                if (firstCriticalIndex == -1) {
                    firstCriticalIndex = currentIndex;
                } else {
                    minDistance = min(minDistance, currentIndex - prevCriticalIndex);
                }
              
                prevCriticalIndex = currentIndex;
            }
            prevNode = currNode;
            currNode = nextNode;
            currentIndex++;
        }

        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        int maxDistance = prevCriticalIndex - firstCriticalIndex;

        return {minDistance, maxDistance};
    }
};
