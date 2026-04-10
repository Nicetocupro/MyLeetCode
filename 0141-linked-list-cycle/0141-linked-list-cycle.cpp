/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        // 快慢指针 或者 set
        if(head == nullptr)
        {
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        while(slow != nullptr && fast != nullptr)
        {
            if(slow == fast)
            {
                return true;
            }
            slow = slow->next;
            fast = fast->next;
            if(fast != nullptr)
            {
                fast = fast->next;
            }
        }

        return false;
    }
};