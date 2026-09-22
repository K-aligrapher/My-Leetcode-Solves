#include <vector>
#include <cstring>

using namespace std;

// Fixed max-size array to eliminate vector allocation overhead completely
struct Node {
    long long prod;
    int remain[6]; 

    void reset() {
        prod = 1;
        memset(remain, 0, sizeof(remain));
    }
};

class Solution {
private:
    int K;
    int N;
    vector<Node> tree;

    // Fully optimized zero-allocation merge process
    void mergeNodes(Node& res, const Node& left, const Node& right) {
        res.prod = (left.prod * right.prod) % K;
        
        // Copy prefixes that end fully inside the left child
        for (int i = 0; i < K; ++i) {
            res.remain[i] = left.remain[i];
        }
        
        // Compute transitions for prefixes that cross into the right child
        long long left_prod = left.prod;
        for (int i = 0; i < K; ++i) {
            if (right.remain[i] > 0) {
                int next_rem = (left_prod * i) % K;
                res.remain[next_rem] += right.remain[i];
            }
        }
    }

    void build(int node, int start, int end, const vector<int>& nums) {
        if (start == end) {
            int rem = nums[start] % K;
            tree[node].prod = rem;
            tree[node].remain[rem] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, nums);
        build(2 * node + 1, mid + 1, end, nums);
        mergeNodes(tree[node], tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            int rem = val % K;
            tree[node].reset();
            tree[node].prod = rem;
            tree[node].remain[rem] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        mergeNodes(tree[node], tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        if (r <= mid) return query(2 * node, start, mid, l, r);
        if (l > mid) return query(2 * node + 1, mid + 1, end, l, r);
        
        Node left_res = query(2 * node, start, mid, l, r);
        Node right_res = query(2 * node + 1, mid + 1, end, l, r);
        
        Node res;
        res.reset();
        mergeNodes(res, left_res, right_res);
        return res;
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // Optimize standard input/output operations for execution speed
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        N = nums.size();
        K = k;
        
        // Single block memory allocation to prevent runtime tree resizing
        tree.resize(4 * N);
        for (int i = 0; i < 4 * N; ++i) {
            tree[i].reset();
        }
        
        build(1, 0, N - 1, nums);
        
        vector<int> result;
        result.reserve(queries.size());
        
        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];
            
            // Perform persistent single element updates 
            update(1, 0, N - 1, idx, val);
            
            // Compute query from start to the absolute end bounds of the array
            Node resNode = query(1, 0, N - 1, start, N - 1);
            
            result.push_back(resNode.remain[x]);
        }
        
        return result;
    }
};
