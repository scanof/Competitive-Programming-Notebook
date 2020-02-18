class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n= coins.size();
        int dp[amount+1];
        for(int i=0;i<=amount;++i) dp[i]= INT_MAX;
        dp[0]=0;
        for(int x: coins) 
            if(x<=amount) dp[x]=1;
        for(int i= 0; i<=amount; ++i)
            for(int x: coins)
                if(i-x>=0 && dp[i-x]!=INT_MAX)
                    dp[i]= min(dp[i], dp[i-x]+1);
        for(int i= 0; i<= amount; ++i){
            cout<< dp[i]<< " ";
        }
        cout<<endl;
        return (dp[amount]==INT_MAX ? -1 : dp[amount]);
    }
};
