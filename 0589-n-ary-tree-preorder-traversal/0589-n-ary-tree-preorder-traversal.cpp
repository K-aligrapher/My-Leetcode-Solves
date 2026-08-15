class Solution {
public:
    vector<int> res;
    void dfs(Node* n)
    {
        if(!n) return;
        res.push_back(n->val);
        for(Node* c : n->children) dfs(c);
    }

    vector<int> preorder(Node* root) {
        dfs(root);
        return res;        
    }
};