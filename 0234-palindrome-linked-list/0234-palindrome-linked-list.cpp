/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        std::stack<ListNode*> myStack;
        ListNode* temp = head;

        while(temp != nullptr)
        {
            myStack.push(temp);
            temp = temp->next;
        }

        temp = head;
        while(temp != nullptr)
        {
            if(temp->val != myStack.top()->val)
            {
                return false;
            }
            temp = temp->next;
            myStack.pop();
        }

        return true;
    }
};