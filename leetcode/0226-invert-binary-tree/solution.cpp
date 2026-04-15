/*
 * @lc app=leetcode id=226 lang=cpp
 *
 * [226] Invert Binary Tree
 */

// @lc code=start
#ifdef LOCAL
#include <iostream>
#include <queue>
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // 这有点简单了，递归解决
        if(root == nullptr)
        {
            return nullptr;
        }

        TreeNode* left = invertTree(root->right);
        TreeNode* right = invertTree(root->left);

        root->left = left;
        root->right = right;

        return root;
    }
};

#ifdef LOCAL
int main()
{

}
#endif
// @lc code=end

