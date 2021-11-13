const int nax = 1e3+20;
const ll inf = LONG_LONG_MAX;
ll dp[nax][nax];
int k[nax][nax];
int C[nax][nax];  // puede depender de k

int main(){
  for(int len=2; len<n; ++len){
    for(int l=0; l< n-len; ++l){
      int r= l+len;
      ll &ans= dp[l][r];
      if(len== 2){
        k[l][r]= l+1;
        ans= C[l][r];
        continue;
      }
      ans= inf;
      for(int i= k[l][r-1]; i<= k[l+1][r]; ++i ){
        if(ans> dp[l][i]+ dp[i][r]){
          ans= dp[l][i] + dp[i][r];
          k[l][r]= i;
        }
      }
      ans+= C[l][r];
    }
  }
  cout<< dp[0][n-1]<<el;
}


