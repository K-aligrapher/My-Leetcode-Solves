class Solution {
public:
    int maximumLengthSubstring(string s) {
    vector<int> freq(26,0);
    int maxLen=0;
    int left=0;

    for(int r=0;r<s.length();r++)
    {
        int currChar = s[r]-'a';
        freq[currChar]++;

        while(freq[currChar]>2)
        {
            int left_char=s[left]-'a';
            freq[left_char]--;
            left++;
        }
        maxLen = max(maxLen,r-left+1);
    }
    return maxLen;
    }
};