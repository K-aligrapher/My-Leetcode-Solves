#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    struct Node { int mx, pr, sf, sz; char cL, cR; };
    vector<Node> tree;

    void merge(int n, int L, int R) {
        auto &p = tree[n], &l = tree[L], &r = tree[R];
        p = {max(l.mx, r.mx), l.pr, r.sf, l.sz + r.sz, l.cL, r.cR};
        if (l.cR == r.cL) {
            if (l.pr == l.sz) p.pr = l.sz + r.pr;
            if (r.sf == r.sz) p.sf = r.sz + l.sf;
            p.mx = max(p.mx, l.sf + r.pr);
        }
        p.mx = max({p.mx, p.pr, p.sf});
    }

    void build(int n, int s, int e, const string& str) {
        if (s == e) { tree[n] = {1, 1, 1, 1, str[s], str[s]}; return; }
        int m = (s + e) / 2;
        build(2 * n, s, m, str); build(2 * n + 1, m + 1, e, str);
        merge(n, 2 * n, 2 * n + 1);
    }

    void update(int n, int s, int e, int idx, char val) {
        if (s == e) { tree[n].cL = tree[n].cR = val; return; }
        int m = (s + e) / 2;
        if (idx <= m) update(2 * n, s, m, idx, val);
        else update(2 * n + 1, m + 1, e, idx, val);
        merge(n, 2 * n, 2 * n + 1);
    }

public:
    vector<int> longestRepeating(string s, string qC, vector<int>& qI) {
        int n = s.size(), q = qI.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, s);
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            update(1, 0, n - 1, qI[i], qC[i]);
            ans[i] = tree[1].mx;
        }
        return ans;
    }
};
