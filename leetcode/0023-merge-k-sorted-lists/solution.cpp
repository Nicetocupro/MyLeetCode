/*
 * @lc app=leetcode id=23 lang=cpp
 *
 * [23] Merge k Sorted Lists
 */

// @lc code=start
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


# ifdef LOCAL
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
};
# endif

class Solution {
public:
    struct Compare
    {
        bool operator()(ListNode* l1, ListNode* l2)
        {
            return l1->val > l2->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, vector<ListNode*>, Compare> myQueue;

        for(auto list : lists)
        {
            ListNode* temp = list;
            while(temp != nullptr)
            {
                myQueue.push(temp);
                temp = temp->next;
            }
        }

        ListNode dummy(0);
        ListNode* temp = &dummy;

        while(!myQueue.empty())
        {
            temp->next = myQueue.top();
            myQueue.pop();
            temp = temp->next;
        }
        temp->next = nullptr;

        return dummy.next;
    }
};

# ifdef LOCAL
int main()
{
    return 0;
}
# endif
// @lc code=end

