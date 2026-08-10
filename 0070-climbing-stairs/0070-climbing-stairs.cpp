class Solution {
public:
    int climbStairs(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;

        int first = 1;
        int second = 2;
        int current = 0;

        for (int i = 3; i <= n; ++i) {
            current = first + second;
            first = second;
            second = current;
        }

        return second;
    }
};
