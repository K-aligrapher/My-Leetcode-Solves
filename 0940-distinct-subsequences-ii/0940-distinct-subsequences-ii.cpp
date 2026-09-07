class Solution {
public:
    int distinctSubseqII(string s) {
        vector<int> endsIn(26,0);
        constexpr int kMod = 1'000'000'007;

        for(char c : s)
        {
            int idx = c-'a';
            long long total=accumulate(endsIn.begin(), endsIn.end(), 0LL);
            endsIn[idx] = (total+1)%kMod;
        }
        long long result = accumulate(endsIn.begin(), endsIn.end(), 0LL);
        return result % kMod;
    }
};