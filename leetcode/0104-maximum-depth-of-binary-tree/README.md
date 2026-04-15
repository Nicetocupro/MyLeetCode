# 0104-maximum-depth-of-binary-tree

## 代码评价

整体写得很规范，BFS 层序遍历思路清晰，`#ifdef LOCAL` 的本地调试技巧也很实用。

---

## 可以改进的地方

**当前 BFS 的小问题：每次循环都调用 `myQueue.size()`**

```cpp
int size = myQueue.size(); // 这行每次循环都重新获取，是对的
```

这里其实没问题，但要注意 `size` 必须在 `for` 循环**之前**快照，你已经做到了，✅

---

## 更值得掌握的方法

### ✅ 方法一：DFS 递归（最简洁，面试首选）

```cpp
int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(maxDepth(root->left), maxDepth(root->right));
}
```

- 两行核心逻辑，思路直观
- 面试时能快速写出，且不易出错
- 时间 O(n)，空间 O(h)（h 为树高，最坏 O(n)）

---

### ✅ 方法二：DFS 迭代（用显式栈模拟递归）

```cpp
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    
    std::stack<std::pair<TreeNode*, int>> stk;
    stk.push({root, 1});
    int result = 0;
    
    while (!stk.empty()) {
        auto [node, depth] = stk.top(); stk.pop();
        result = std::max(result, depth);
        if (node->left)  stk.push({node->left,  depth + 1});
        if (node->right) stk.push({node->right, depth + 1});
    }
    return result;
}
```

- 避免递归栈溢出（极深树时有优势）
- 面试中展示这个能体现对栈帧的理解

---

## 三种方法对比

| 方法 | 代码量 | 空间 | 适用场景 |
|------|--------|------|----------|
| DFS 递归 | ⭐ 最少 | O(h) | 面试快速作答 |
| BFS 迭代（你的） | 中等 | O(w)（w为最大宽度） | 需要按层处理时 |
| DFS 迭代 | 中等 | O(h) | 避免栈溢出 |

---

## 总结

你的 BFS 解法**完全正确且工程质量不错**，没有硬伤。建议额外熟练掌握 **DFS 递归版**，面试中两行写完再口述 BFS 思路，能展示你对多种解法的掌握。