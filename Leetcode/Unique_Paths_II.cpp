class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m= obstacleGrid.size();
        int n= obstacleGrid[0].size();
        long long grid[m+1][n+1];
        memset(grid, 0, sizeof grid);
        if(obstacleGrid[0][0]==1 || obstacleGrid[m-1][n-1]==1) return 0;
        grid[1][1]=1;
        cout<< "pasado\n";
        for(int i=1; i<= m; ++i){
            cout<<"i "<<i<<endl;
            for(int j= 1; j<=n ; ++j){
                
                cout<<"j "<<j<<endl;    
                if(obstacleGrid[i-1][j-1]==0){
                    grid[i][j]+= grid[i-1][j]+ grid[i][j-1];
                } 
            }
        }
        
        cout<< "repasado\n";
        return grid[m][n];
    }
};
