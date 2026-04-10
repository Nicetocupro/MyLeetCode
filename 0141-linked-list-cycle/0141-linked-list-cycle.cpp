class Solution {
public:
    bool hasCycle(ListNode *head) {
        // 快慢指针 或者 set
        if(head == NULL)
        {
            return false;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        while(fast != NULL && fast->next != NULL)
        {
            if(slow == fast)
            {
                return true;
            }
            slow = slow->next;
            fast = fast->next->next;
        }

        return false;
    }
};
