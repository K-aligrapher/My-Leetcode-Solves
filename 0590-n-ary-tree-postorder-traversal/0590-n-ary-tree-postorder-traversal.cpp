class Solution {
public:
    vector<int>res;

    void dfs(Node* n)
    {
        if(!n) return ;
        for(Node* c : n->children) dfs(c);
        res.push_back(n->val);
    }
    vector<int> postorder(Node* root) {
        dfs(root);
        return res;
    }
};