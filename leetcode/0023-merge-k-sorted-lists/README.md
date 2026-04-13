# LeetCode 23 - Merge K Sorted Lists 笔记

## 题目

将 k 条已排序链表合并成一条排好序的链表。

---

## 解法一：优先队列（全量入堆）

```cpp
class Solution {
public:
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        for (auto list : lists) {
            ListNode* temp = list;
            while (temp != nullptr) {
                pq.push(temp);
                temp = temp->next;
            }
        }

        ListNode dummy(0);
        ListNode* temp = &dummy;

        while (!pq.empty()) {
            temp->next = pq.top();
            pq.pop();
            temp = temp->next;
        }
        temp->next = nullptr;

        return dummy.next;
    }
};
```

**时间**：O(n log n)　**空间**：O(n)

把所有节点全压入堆，出堆顺序天然有序，每次 `temp->next` 的赋值会覆盖旧的 next 指针，最后一个节点用 `temp->next = nullptr` 收尾，不存在指针残留问题。

---

## 解法二：优先队列（只压 k 个头节点）⭐ 推荐

```cpp
class Solution {
public:
    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        // 只压入每条链表的头节点，堆内始终最多 k 个元素
        for (ListNode* head : lists)
            if (head) pq.push(head);

        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (!pq.empty()) {
            ListNode* node = pq.top(); pq.pop();
            tail->next = node;
            tail = tail->next;
            if (node->next) pq.push(node->next); // 弹出一个补入下一个
            tail->next = nullptr;
        }

        return dummy.next;
    }
};
```

**时间**：O(n log k)　**空间**：O(k)

与解法一相比，堆内节点数从 O(n) 降到 O(k)，时间复杂度也从 O(n log n) 降到 O(n log k)，是优先队列写法的标准形式。

---

## 解法三：分治归并 ⭐ 进阶

思路与归并排序完全一致，两两合并，每轮减半，共 log k 轮。

```
第一轮：[L0,L1] [L2,L3] [L4,L5] ...  →  k/2 条
第二轮：[L01,L23] ...                 →  k/4 条
...
```

```cpp
class Solution {
private:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (a && b) {
            if (a->val <= b->val) { tail->next = a; a = a->next; }
            else                  { tail->next = b; b = b->next; }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        return dummy.next;
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int n = lists.size();
        while (n > 1) {
            for (int i = 0; i < n / 2; i++)
                lists[i] = mergeTwoLists(lists[i], lists[i + (n + 1) / 2]);
            n = (n + 1) / 2;
        }
        return lists[0];
    }
};
```

**时间**：O(n log k)　**空间**：O(log k) 递归栈

不依赖任何额外数据结构，空间最优，面试中作为进阶写法能加分。

---

## 三种解法对比

| 解法 | 时间 | 空间 | 推荐度 |
|---|---|---|---|
| 全量入堆 | O(n log n) | O(n) | ★★★ |
| 只压 k 个头节点 | O(n log k) | O(k) | ★★★★★ |
| 分治归并 | O(n log k) | O(log k) | ★★★★★ |

---

## 知识点

**最小堆的自定义比较器**：`>` 表示小的优先（最小堆），`<` 表示大的优先（最大堆）。

```cpp
// 最小堆（val 小的先出）
struct Compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val; // 返回 true 表示 a 优先级低
    }
};
```

**dummy 节点技巧**：处理链表头部边界，避免对第一个节点做特殊判断，几乎所有链表构建题都可以用。

```cpp
ListNode dummy(0);
ListNode* tail = &dummy;
// ... 构建链表 ...
return dummy.next;
```

**分治模板（原地折叠）**：

```cpp
int n = lists.size();
while (n > 1) {
    for (int i = 0; i < n / 2; i++)
        lists[i] = merge(lists[i], lists[i + (n + 1) / 2]);
    n = (n + 1) / 2;
}
```

`(n + 1) / 2` 处理 k 为奇数时最后一条链表的配对，避免越界。

---

## 相关题目

- LeetCode 21 — Merge Two Sorted Lists（本题子问题）
- LeetCode 148 — Sort List（链表归并排序，分治结构相同）
- LeetCode 373 — Find K Pairs with Smallest Sums（优先队列维护 k 个候选）