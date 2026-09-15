class Solution {
public:
    bool judgeCircle(string moves) {
       int x=0, y=0;
       for(char m : moves)
       {
        switch(m)
        {
            case 'L' : x--;
            break;
            case 'R' : x++;
            break;
            case 'U' : y++;
            break;
            case 'D' : y--;
        }
       }
       if(x==0 && y==0) return true;
       return false; 
    }
};