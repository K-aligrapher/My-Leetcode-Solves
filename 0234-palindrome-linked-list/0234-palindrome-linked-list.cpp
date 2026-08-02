class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;

        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while (curr != nullptr) {
            ListNode* next_node = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_node;
        }

        ListNode* first_half = head;
        ListNode* second_half = prev; 
        bool result = true;

        while (second_half != nullptr) {
            if (first_half->val != second_half->val) {
                result = false;
                break;
            }
            first_half = first_half->next;
            second_half = second_half->next;
        }

        return result;
    }
};
