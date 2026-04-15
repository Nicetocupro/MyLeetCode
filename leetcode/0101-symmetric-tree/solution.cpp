/*
 * @lc app=leetcode id=101 lang=cpp
 *
 * [101] Symmetric Tree
 */

// @lc code=start
#ifdef LOCAL
#include <iostream>
#include <stack>

struct TreeNode {
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
    bool isSymmetric(TreeNode* root) {
        if(root == nullptr)
        {
            return true;
        }
        
        if(root->left == nullptr || root->right == nullptr)
        {
            return root->left == root->right;
        }
        
        // 从根节点出发 双指针观察是否一致
        std::stack<TreeNode*> leftStack;
        std::stack<TreeNode*> rightStack;

        leftStack.push(root->left);
        rightStack.push(root->right);

        while(!leftStack.empty() || !rightStack.empty())
        {
            if(leftStack.size() != rightStack.size())
            {
                return false;
            }

            int size = leftStack.size();

            for(int i = 0; i < size; i++)
            {
                TreeNode* leftTemp = leftStack.top();
                TreeNode* rightTemp = rightStack.top();
                leftStack.pop();
                rightStack.pop();

                if(leftTemp->val != rightTemp->val)
                {
                    return false;
                }

                if(leftTemp->left != nullptr && rightTemp->right != nullptr)
                {
                    leftStack.push(leftTemp->left);
                    rightStack.push(rightTemp->right);
                }
                else if(leftTemp->left == nullptr && rightTemp->right == nullptr)
                {

                }
                else
                {
                    return false;
                }


                if(leftTemp->right != nullptr && rightTemp->left != nullptr)
                {
                    leftStack.push(leftTemp->right);
                    rightStack.push(rightTemp->left);
                }
                else if(leftTemp->right == nullptr && rightTemp->left == nullptr)
                {

                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }
};

#ifdef LOCAL
int main()
{

}
#endif
// @lc code=end

