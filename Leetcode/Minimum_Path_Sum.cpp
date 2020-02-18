class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n= grid.size();
        int m= grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        for(int i=0; i<n; ++i)
            for(int j=0; j<m ; ++j)
                    dp[i][j]= grid[i][j];              
        
        for(int i=0; i<n; ++i)
            for(int j=0; j<m ; ++j)
                if(i-1>=0 && j-1>=0)  dp[i][j]+= min(dp[i][j-1],dp[i-1][j]);
                else if(i-1>=0) dp[i][j]+= dp[i-1][j];
                else if(j-1>=0) dp[i][j]+= dp[i][j-1];
        
        for(int i=0; i<n; ++i){
            for(int j=0; j<m ; ++j)
                    cout<< dp[i][j]<< " "; 
            cout<<endl;   
        }
        return dp[n-1][m-1];
    }
};
