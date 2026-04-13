/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node dummy(0);
        Node* newTemp = &dummy;
        Node* prev = &dummy;
        Node* temp = head;
        std::unordered_map<Node*, Node*> myMap;

        while(temp != nullptr)
        {
            newTemp->next = new Node(temp->val);
            prev->next = newTemp->next;

            myMap[temp] = newTemp->next;
            temp = temp->next;
            newTemp = newTemp->next;
            prev = prev->next;
        }

        newTemp->next = nullptr;

        newTemp = dummy.next;
        temp = head;

        while(temp != nullptr)
        {
            if(temp->random == nullptr)
            {
                newTemp->random = nullptr;
            }
            else
            {
                newTemp->random = myMap[temp->random];
            }

            newTemp = newTemp->next;
            temp = temp->next;
        }

        return dummy.next;
    }
};