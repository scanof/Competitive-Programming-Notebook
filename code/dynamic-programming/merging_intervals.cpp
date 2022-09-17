// Option 1
for(int len= 0; len<n; ++len){
    for(int l= 0; l<n-len; ++l){
        int r= l+len;
        dp[l][r]= max(dp[l+1][r], dp[l][r-1]);
    }
}
// Option 2
for(int l= n-1; l>=0; --l){
    for(int r= l; r<n ; ++r){
        dp[l][r]= max(dp[l+1][r], dp[l][r-1]);
    }
}
