// https://www.spoj.com/problems/BRKSTRNG/
#include <bits/stdc++.h>
#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define fore(i,l,r) for(int i=l; i<=r; ++i)

using namespace std;

typedef long long ll;

const int N = 1e3+20;
const ll inf = 1e18;
ll dp[N][N];
int op[N][N], a[N];

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int k, n; 
  while(cin >> k >> n && k+n){
    for1(i, n) cin >> a[i];
    a[n+1] = k;
    n += 2;  // Add 0, k as interval ends [0, a_1, a_2, ... a_n, k]

    fore(len, 2, n-1){  // Compute in increasing size order
      forn(l, n-len){  
        int r = l + len;
        ll& ans = dp[l][r] = inf;
        if(len == 2){   // Base case (could need modification)
          op[l][r] = l+1;
          ans = a[r] - a[l];
          continue;
        }
        fore(i, op[l][r-1], op[l+1][r]){    // Recursion in optimum range 
          if(ans > dp[l][i] + dp[i][r]){    // op[l][r] in [ op[l][r-1], op[l+1][r] ]
            ans = dp[l][i] + dp[i][r];      // Reduces O(N^3) to O(N^2)
            op[l][r] = i;
          }
        }
        ans += a[r] - a[l]; // Add Cost[l][r] to ans = dp[l][r]
      }
    }
    cout << dp[0][n-1] << endl;
  }
}


