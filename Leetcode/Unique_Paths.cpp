class Solution {
public:
    int uniquePaths(int m, int n) {
        int grid[m+1][n+1];
        memset(grid, 0, sizeof grid);
        grid[1][1]= 1;
        for(int i= 1 ; i<=m; ++i){
            for(int j=1; j<=n; ++j){
                grid[i][j]+= grid[i][j-1] + grid[i-1][j];
            }
        }
        return grid[m][n];
    }
};
