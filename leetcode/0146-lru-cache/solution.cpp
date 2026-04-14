/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 */
#ifdef LOCAL
#include <iostream>
#include <unordered_map>
#endif
// @lc code=start

struct Node{
    int key, val;
    Node *prev, *next;
    Node(int key, int value): key(key), val(value), prev(nullptr), next(nullptr){};
};

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;

    }
    
    int get(int key) {
        if(map.count(key))
        {
            Node* node = map[key];

            remove(node);
            addTohead(node);

            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(map.count(key))
        {
            Node* node = map[key];
            node->val = value;
            remove(node);
            addTohead(node);
            return;
        }

        Node* node = new Node(key, value);
        map[key] = node;
        addTohead(node);

        if(map.size() > cap)
        {
            // 删除尾节点
            Node* node = tail->prev;
            node->prev->next = tail;
            tail->prev = node->prev;
            map.erase(node->key);

            delete node;
        }
    }

    void printAllNode()
    {
        Node* temp = head->next;
        while(temp != nullptr)
        {
            std::cout << temp->key << " " << temp->val << std::endl;
            temp = temp->next; 
        }
    }
private:
    int cap;
    Node* head, *tail;
    std::unordered_map<int, Node*> map;

    void remove(Node *node)
    {
        // 从当时的位置离开
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addTohead(Node* node)
    {
        // 加入头节点
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }
};

#ifdef LOCAL
int main()
{
    LRUCache* lRUCache = new LRUCache(2);
    lRUCache->put(2, 1); // cache is {1=1}
    lRUCache->printAllNode();
    std::cout << std::endl;

    lRUCache->put(1, 1); // cache is {1=1, 2=2}
    lRUCache->printAllNode();
    std::cout << std::endl;

    lRUCache->put(2, 3);
    lRUCache->printAllNode();
    std::cout << std::endl;
    
    lRUCache->put(4, 1);
    // lRUCache->printAllNode();
    std::cout << std::endl;

    std::cout << lRUCache->get(1) << std::endl;    // return 1
    std::cout << lRUCache->get(2) << std::endl;
    lRUCache->printAllNode();
    // lRUCache->put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
        // returns -1 (not found)
    // lRUCache->put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    // std::cout << lRUCache->get(1) << std::endl;    // return -1 (not found)
    // std::cout << lRUCache->get(3) << std::endl;    // return 3
    // std::cout << lRUCache->get(4) << std::endl;    // return 4

    return 0;
}
#endif

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

