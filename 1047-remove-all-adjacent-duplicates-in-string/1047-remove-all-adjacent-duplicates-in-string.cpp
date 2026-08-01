class Solution {
public:
    string removeDuplicates(string s) {
          string k;
          for(char i : s)
          {
            if(!k.empty() && i == k.back())
            k.pop_back();

            else
            k.push_back(i);
          }
          return k;
    }
};