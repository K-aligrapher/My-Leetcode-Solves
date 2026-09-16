#include <vector>

class Solution {
public:
    int numberOfSets(int n, int k) {
        long long mod = 1'000'000'007;
        
        // We need to calculate (n + k - 1) Choose (2 * k)
        long long total_points = n + k - 1;
        long long choose_endpoints = 2 * k;
        
        if (choose_endpoints > total_points) return 0;
        
        long long numerator = 1;
        long long denominator = 1;
        
        for (long long i = 1; i <= choose_endpoints; ++i) {
            numerator = (numerator * (total_points - i + 1)) % mod;
            denominator = (denominator * i) % mod;
        }
        
        // Fermat's Little Theorem for Modular Inverse: inv(x) = x^(mod-2) % mod
        return (numerator * modularInverse(denominator, mod - 2, mod)) % mod;
    }

private:
    long long modularInverse(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }
};
