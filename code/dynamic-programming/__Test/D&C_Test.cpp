// https://codeforces.com/problemset/problem/321/E
#include <bits/stdc++.h>
#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define fore(i,l,r) for(int i=l; i<=r; ++i)
#define d(x) cout << #x << " : " << x<< endl;

using namespace std;

typedef long long ll;

const int N = 4e3 + 20, K = 801, inf = 2e9;
int C[N][N], c[N][N], dp[K][N], n;  // C[l][r], cost of cutting the interval [l, r]

void compute(int k, int l, int r, int optl, int optr){
  if(l > r) return;
  int mid = (l+r)/2, opt = -1;
  int& ans = dp[k][mid] = inf;

  fore(i, max(mid, optl), optr)       // Find ans and optimum for mid 
    if(ans > C[mid][i] + dp[k-1][i+1]) ans = C[mid][i] + dp[k-1][i+1], opt = i;

  compute(k, l, mid-1, optl, opt);    // Compute left half
  compute(k , mid+1, r, opt, optr);   // Compute right half
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, k; cin >> n >> k;
  --k;    // K pieces are obtained from k-1 cuts
  for1(i, n) for1(j, n) cin >> c[i][j];
  
  // Compute Cost function C
  for1(i, n){
    int sum = 0;
    for1(j, n) sum += c[i][j], c[i][j] = sum;
  }
  for1(j, n){
    int sum = 0;
    for1(i, n) sum += c[i][j], c[i][j] = sum;
  }
  for1(i, n) 
    fore(j, i, n) C[i][j] = c[j][j] - c[i-1][j] - c[j][i-1] + c[i-1][i-1];

  for1(i, n) dp[0][i] = C[i][n];     // Base case: 0 cuts, from i to n
  for1(i, k) compute(i, 1, n, 1, n); // Compute for k = 1, 2, 3 ... cuts 

  cout << dp[k][1] / 2 << endl;
}