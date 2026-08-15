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
class Solution {
public:
    int check(TreeNode* n)
    {
        if(!n) return 0;
        int L=check(n->left);
        if(L==-1) return -1;
        int R=check(n->right);
        if(R==-1 || abs(L-R)>1) return -1;
        return 1+max(L,R);
    }

    bool isBalanced(TreeNode* root) {
        return check(root)!=-1;
    }
};