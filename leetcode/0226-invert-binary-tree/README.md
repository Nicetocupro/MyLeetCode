# 0226-invert-binary-tree

## 代码评价

逻辑完全正确，递归思路清晰。但有一个小的代码风格问题值得注意。

---

## 一个小优化：可以去掉临时变量

你用了 `left` / `right` 两个临时变量来避免覆盖，思路是对的，但其实可以直接用 `std::swap` 更简洁：

```cpp
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return nullptr;
    invertTree(root->left);
    invertTree(root->right);
    std::swap(root->left, root->right);
    return root;
}
```

或者更紧凑的写法：

```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    std::swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
```

两种写法等价，先递归后交换、或先交换后递归均可。

---

## 值得掌握的迭代写法（BFS）

```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        std::swap(node->left, node->right);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return root;
}
```

逻辑很直观：每访问一个节点就交换其左右子节点，然后把子节点入队继续处理。

---

## 总结

| 方法 | 代码量 | 说明 |
|------|--------|------|
| 递归 + 临时变量（你的） | 稍多 | 正确，略显冗余 |
| 递归 + `std::swap` | ⭐ 最简 | 面试推荐 |
| BFS 迭代 | 中等 | 展示广度遍历能力 |

这题本身不难，面试重点在于能否**快速写出简洁的递归**，同时口头提及"也可以用 BFS/DFS 迭代实现"来展示全面性。