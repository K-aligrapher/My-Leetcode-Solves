class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int charcount[26]={0};

        for(char c : magazine)
        charcount[c-'a']++;

        for(char c : ransomNote)
        {
            charcount[c-'a']--;
            if(charcount[c-'a']<0)
            return false;
        }
        return true;
    }
};