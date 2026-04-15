# 0101-symmetric-tree

## 代码评价

逻辑正确，双栈镜像对比的思路是对的。但代码有几处可以明显简化。

---

## 问题一：开头的特判是多余的

```cpp
if(root->left == nullptr || root->right == nullptr)
{
    return root->left == root->right;
}
```

这个判断完全可以删掉，后续的迭代逻辑已经能处理这种情况，属于冗余代码。(这个在我的逻辑里没办法删掉，因为我不允许`nullptr`入栈)

---

## 问题二：`size` 快照 + for 循环是多余的

你用了类似 BFS 按层处理的写法，但这题的栈里每次 pop 一个处理一个就够了，**不需要按层批量处理**。两个栈始终保持同步 push/pop，size 必然相等，`size` 检查和 for 循环可以去掉。

---

## 问题三：if/else if/else 结构可以用辅助函数收拢

对左右子节点的四种 null 组合分别讨论，逻辑重复且啰嗦。

---

## 改进后的迭代写法

```cpp
bool isSymmetric(TreeNode* root) {
    std::stack<TreeNode*> leftStack, rightStack;
    leftStack.push(root->left);
    rightStack.push(root->right);

    while (!leftStack.empty()) {
        TreeNode* l = leftStack.top(); leftStack.pop();
        TreeNode* r = rightStack.top(); rightStack.pop();

        if (!l && !r) continue;       // 两边都为空，对称，继续
        if (!l || !r) return false;   // 一边为空，不对称
        if (l->val != r->val) return false;

        // 镜像入栈
        leftStack.push(l->left);  rightStack.push(r->right);
        leftStack.push(l->right); rightStack.push(r->left);
    }
    return true;
}
```

允许 null 入栈，用 `continue` 处理，逻辑更线性清晰。

---

## 更推荐的递归写法（面试首选）

```cpp
bool check(TreeNode* l, TreeNode* r) {
    if (!l && !r) return true;
    if (!l || !r) return false;
    return l->val == r->val
        && check(l->left,  r->right)
        && check(l->right, r->left);
}

bool isSymmetric(TreeNode* root) {
    return check(root->left, root->right);
}
```

逻辑与迭代版完全对应，但更简洁，面试中能快速写出。

---

## 总结

| 方法 | 问题 |
|------|------|
| 你的双栈迭代 | 正确，但特判冗余、for循环多余、null处理啰嗦 |
| 改进迭代版 | 允许null入栈，逻辑线性，简洁 |
| 递归版 | ⭐ 面试推荐，最简洁直观 |