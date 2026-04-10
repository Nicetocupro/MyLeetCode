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
        std::unordered_set<ListNode*> mySet;
        ListNode* temp = head;
        while(temp != nullptr)
        {
            if(!mySet.contains(temp))
            {
                mySet.insert(temp);
            }
            else
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};