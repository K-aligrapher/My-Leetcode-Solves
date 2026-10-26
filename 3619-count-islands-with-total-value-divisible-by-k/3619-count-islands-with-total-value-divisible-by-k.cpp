class Solution {

private:
    long long dfs(int r, int c, vector<vector<int>>& grid)
    {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] == 0) {
        return 0;
    }
    long long sum=grid[r][c];
    grid[r][c]=0;

    sum+=dfs(r,c+1,grid);
    sum+=dfs(r,c-1,grid);
    sum+=dfs(r+1,c,grid);
    sum+=dfs(r-1,c,grid);

    return sum;
    }
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int rows=grid.size();
        if(rows==0) return 0;
        int column=grid[0].size();
        int val=0;

        for(int r=0;r<rows;r++)
        for(int c=0;c<column;c++)
        {
            if(grid[r][c]!=0)
            {
            long long total=dfs(r,c,grid);

            if(total % k==0)
            val++;
            }
        }
        return val;
    }
};