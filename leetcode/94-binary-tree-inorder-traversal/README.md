# 94-binary-tree-inorder-traversal

## 代码分析

你直接用**迭代 + 显式栈**实现中序遍历，跳过了递归版本，说明你对这道题理解得很透彻。代码逻辑清晰，没有 bug，是这道题的标准最优解。

---

## 唯一值得一提的：Morris Traversal

这是一种 **O(1) 空间**的遍历方法，不用栈也不用递归，通过临时修改树的指针来记录"回退路径"。

### 核心思想

这个方法确实厉害，仔细想了想确实是这样，每次到左子树的最右节点都会回到本节点。

中序遍历中，访问一个节点之前必须先访问它的**左子树的最右节点（inorder predecessor）**。Morris 利用这个节点的空 `right` 指针，暂时指回当前节点作为"线索"，遍历完左子树后再沿线索回来，最后恢复原指针。

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;

    while (curr) {
        if (!curr->left) {
            // 没有左子树，直接访问，去右边
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // 找左子树的最右节点（inorder predecessor）
            TreeNode* pre = curr->left;
            while (pre->right && pre->right != curr)
                pre = pre->right;

            if (!pre->right) {
                // 第一次到达：建立线索，深入左子树
                pre->right = curr;
                curr = curr->left;
            } else {
                // 第二次到达：左子树已遍历完，访问当前节点，断开线索
                pre->right = nullptr;
                result.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    return result;
}
```

### 图示流程（以你 main 里的树为例）
```
    1
     \
      2
     /
    3
```
这棵树没有左子树，Morris 会直接退化成顺序访问，输出 `1 3 2`，和你的结果一致。

---

## 总结

| 方法 | 时间 | 空间 | 说明 |
|------|------|------|------|
| 递归 | O(n) | O(h) | 最直观 |
| 迭代+栈（你的） | O(n) | O(h) | ✅ 面试标准答案 |
| Morris Traversal | O(n) | **O(1)** | 进阶，会临时修改树结构 |

你的实现已经是面试中的最优解。Morris 是竞赛/追求极致空间时才需要掌握的技巧，了解思想即可，不必强求。