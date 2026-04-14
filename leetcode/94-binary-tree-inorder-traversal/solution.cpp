/*
 * @lc app=leetcode id=94 lang=cpp
 *
 * [94] Binary Tree Inorder Traversal
 */
#ifdef LOCAL
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
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
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode* temp = root;
        vector<int> result;
        stack<TreeNode*> myStack;

        while(temp != nullptr || !myStack.empty())
        {
            if(temp != nullptr)
            {
                myStack.push(temp);
                temp = temp->left;
            }
            else
            {
                temp = myStack.top();
                myStack.pop();
                result.push_back(temp->val);
                temp = temp->right;
            }
        }

        return result;
    }
};

#ifdef LOCAL

int main()
{
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);
    
    Solution s;

    vector<int> results = s.inorderTraversal(root);

    for(auto result : results)
    {
        std::cout << result << std::endl;
    }

    return 0;
}
 
#endif
// @lc code=end

