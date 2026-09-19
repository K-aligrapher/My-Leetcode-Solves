class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int count=0;
        for(char jewel : jewels)
        {
            for(char stone : stones)
            {
                if(stone == jewel)
                count++;
            }
        }
        return count;
    }
};