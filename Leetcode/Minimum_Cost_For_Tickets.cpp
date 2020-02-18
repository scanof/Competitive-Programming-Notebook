class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size(); 
        int ma=0;
        int pas[3]={1,7,30};
        for(int x: days) ma= max(ma, x);
        vector<bool> obli(ma+1);
        vector<int> costo(ma+1);
        for(int x: days){
            obli[x]=true;
        }
        vector<int> dp(ma+1,INT_MAX);
        dp[0]=0;
        for(int i=1; i<= ma; ++i){
            if(obli[i]){
                for(int j=0; j<3; ++j){
                    int m = (i-pas[j]>=0 ? dp[i-pas[j]] : 0 ) + costs[j];
                    dp[i]= min(dp[i], m );
                }
            }else{
                dp[i]= dp[i-1];
            }
        }
        return dp[ma];
    }
};
