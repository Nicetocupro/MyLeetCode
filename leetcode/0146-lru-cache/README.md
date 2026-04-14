# lru Cache

## 代码分析

你的实现思路完全正确，是 LRU Cache 的**标准解法**：哈希表 + 双向链表，整体质量很高。

### 小问题

**内存泄漏**：析构函数缺失，`head`、`tail` 以及所有缓存节点没有被释放。

```cpp
~LRUCache() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}
```

**变量遮蔽（shadow variable）**：`put()` 里重复声明了 `Node* node`，内层的覆盖了外层，虽然逻辑碰巧没错，但编译器会告警，建议换个名字：

```cpp
// 删除尾节点
Node* lru = tail->prev;   // 换名避免遮蔽
...
delete lru;
```

---

## 值得学习的点

### 1. 抽取 `removeTail()` 提高可读性

`put()` 里删除尾节点的逻辑和 `remove()` 高度重合，可以直接复用：

```cpp
void put(int key, int value) {
    // ...
    if (map.size() > cap) {
        Node* lru = tail->prev;
        remove(lru);           // 直接复用已有方法
        map.erase(lru->key);
        delete lru;
    }
}
```

这样逻辑更统一，`remove()` 本来就是通用的，不必在外面再手写一遍指针操作。

---

### 2. 用 `std::list` + `iterator` 的标准库写法

C++ 标准库的 `std::list` 内部就是双向链表，配合 `splice()` 可以 O(1) 移动节点，不需要手动管理内存：

```cpp
class LRUCache {
    int cap;
    list<pair<int,int>> lst;   // front = 最新, back = 最旧
    unordered_map<int, list<pair<int,int>>::iterator> map;
public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (!map.count(key)) return -1;
        // splice 把节点移到 front，O(1)
        lst.splice(lst.begin(), lst, map[key]);
        return map[key]->second;
    }

    void put(int key, int value) {
        if (map.count(key)) {
            map[key]->second = value;
            lst.splice(lst.begin(), lst, map[key]);
            return;
        }
        lst.push_front({key, value});
        map[key] = lst.begin();
        if ((int)map.size() > cap) {
            map.erase(lst.back().first);
            lst.pop_back();
        }
    }
};
```

核心是 `splice(dest, src, it)`：把 `it` 指向的节点**从原位置摘出，接到 dest 前面**，不涉及内存分配，迭代器依然有效。这是面试中展示 STL 熟悉度的好机会。

---

## 总结

| 维度 | 你的实现 | `std::list` 写法 |
|------|---------|----------------|
| 思路 | ✅ 完全正确 | 相同 |
| 内存管理 | 需补析构函数 | 自动管理 |
| 代码量 | 稍多 | 更简洁 |
| 面试适用性 | ✅ 展示底层理解 | ✅ 展示 STL 熟悉度 |

你手写双向链表的版本其实更适合面试，能展示你理解底层指针操作。`std::list` 版是工程中更实用的写法。两种都掌握最好。