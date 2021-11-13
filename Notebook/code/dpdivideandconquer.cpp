const ll inf = 1e18;
const int nax = 1e3+20, kax = 20;

ll C[nax][nax], dp[kax][nax];
int n;

void compute(int k, int l, int r, int optl, int optr){
  if(l>r) return ;
  int mid= (l+r)/2, opt;
  pll best= {inf,-1};
  for(int i= max(mid,optl); i<= optr ; ++i ){
    best = min(best, {dp[k-1][i+1] + C[mid][i] ,i}  );
  }
  tie(dp[k][mid], opt) = best;
  compute(k,l, mid-1, optl, opt);
  compute(k,mid+1, r, opt, optr);
}

inside main(){
  fore(k,1,K) // definir el caso base k = 0.
    compute(k,0,n-1,0,n-1);
}
