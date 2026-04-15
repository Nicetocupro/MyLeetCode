/*
 * @lc app=leetcode id=104 lang=cpp
 *
 * [104] Maximum Depth of Binary Tree
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
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

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if(root == nullptr)
        {
            return 0;
        }
        
        // 深度遍历 dfs
        int result = 0;
        std::queue<TreeNode *> myQueue;
        myQueue.push(root);

        while (!myQueue.empty())
        {
            int size = myQueue.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *temp = myQueue.front();
                myQueue.pop();

                // std::cout << temp->val << " ";

                if (temp->left != nullptr)
                {
                    myQueue.push(temp->left);
                }

                if (temp->right != nullptr)
                {
                    myQueue.push(temp->right);
                }
            }
            // std::cout << std::endl;
            result++;
        }
        return result;
    }
};

#ifdef LOCAL
int main()
{
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    Solution s;
    std::cout << s.maxDepth(root) << std::endl;

    return 0;
}
#endif
// @lc code=end
