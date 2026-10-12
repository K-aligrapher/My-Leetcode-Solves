class Solution {
public:
    int hammingDistance(int x, int y) {
        int xorres=x^y;
        int distance=0;

        while(xorres>0)
        {
            xorres &= (xorres-1);
            distance++;
        }
        return distance;
    }
};