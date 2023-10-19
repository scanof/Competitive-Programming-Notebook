// https://codeforces.com/gym/103185/problem/F
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define fore(i,l,r) for(int i=l; i <= r; ++i)
#define fored(i,l,r) for(int i=r; i >= l; --i)
#define el '\n'
#define d(x) cout << #x << " : " << x << el;
#define all(v) v.begin(),v.end()
#define sz(v) int(v.size())


using namespace std;

typedef long long ll;
typedef vector<ll> vi;
const ll inf = 1e18;
const int N = 8e3 + 20, K = 13;  //K  has to satisfy K> log nax + 1
ll st[N][K];
struct RMQ{
  ll neutro = inf;
  inline ll oper(ll a, ll b){ return a < b ? a : b; }
  RMQ(vi& a){
    forn(i, sz(a)) st[i][0] = a[i];
    for1(j, K-1)
      forn(i, sz(a) - (1 << j) + 1)
        st[i][j] = oper(st[i][j-1], st[i + (1 << (j-1))][j-1]);
  }
  ll query(int l, int r){
    if(l > r) return neutro;
    int j = 31 - __builtin_clz(r-l+1);
    return oper(st[l][j], st[r - (1 << j) + 1][j]);
  }
};

vi dp[N];
int n;
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> n; 
  vi a(n); forn(i, n) cin >> a[i];
  
  vi b = a;  sort(all(b), greater<>());
  ll ans[n][2], sum = 0;
  forn(i, n){
    dp[i].resize(n);
    ans[i][1] = sum += b[i];
  }

  vector<int> nex(n, n);
  forn(i, n){
    fore(j, i+1, n-1){
      if(a[j] >= a[i]){
        nex[i] = j; break;
      }
    }
  }

  ll mx = 0;
  fored(i, 0, n-1){
    mx = max(mx, a[i]);
    dp[0][i] = mx;
  }
  RMQ st(dp[0]);
  ans[0][0] = dp[0][0];

  for1(k, n-1){
    dp[k][n-k-1] = a[n-k-1] + dp[k-1][n-k];
    fored(i, 0, n-k-2){
      int r = nex[i];
      dp[k][i] = r <= n-k-1 ? dp[k][r] : inf;
      r = min(r, n-k);
      dp[k][i] = min(dp[k][i], a[i] + st.query(i+1, r));
    }

    ans[k][0] = dp[k][0];
    st = RMQ(dp[k]);
  }

  forn(i, n) cout << ans[i][0] << " " << ans[i][1] << el;
} 
