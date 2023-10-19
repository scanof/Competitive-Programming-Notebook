// https://codeforces.com/problemset/problem/894/E
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) v.size()
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << ": " << x <<  el;

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

const int N = 1e6 + 10, mx = 1e8;

int n, m;
vi tr, ts; 
vll sum;
ll csum[N];

vii g[N], gr[N], g2[N];
int scc[N], comp;
bool seen[N];
void dfs1(int u){
  seen[u] = 1;
  for(auto&[v, _]: g[u]) if(!seen[v]) dfs1(v);
  ts.pb(u);
}
void dfs2(int u){
  scc[u] = comp;
  for(auto&[v, _]: gr[u]) if(scc[v] == -1) dfs2(v);
}

int find_scc(int n){
  forn(i, n) if(!seen[i]) dfs1(i);
  reverse(all(ts));
  memset(scc, -1, sizeof scc);
  for(int u: ts) if(scc[u] == -1) ++comp, dfs2(u);
  return comp;
}

void pre(){
  tr.pb(0); sum.pb(0);
  int i=1, t=1; ll su=1;
  while(t <= mx){
    tr.pb(t);
    sum.pb(su);
    ++i;
    t += i;
    su += ll(i)*i;
  }
}

ll calc(int num){
  int i = upper_bound(all(tr), num) - tr.begin() - 1;
  int dif = num - tr[i];
  return sum[i] + ll(i+1) * dif;
}

ll dp[N];
ll go(int v){
  ll& r = dp[v];
  if(r != -1) return r;
  
  ll best = 0;
  for(auto&[u, w] : g2[v]) best = max(best, w + go(u));
  return r = csum[v] + best;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> n >> m;
  forn(i, m){
    int u, v, w; cin >> u >> v >> w;
    --u, --v;
    g[u].pb({v, w});
    gr[v].pb({u, w});
  }
  pre();

  find_scc(n);  
  forn(i, n){
    for(auto&[v, w]: g[i]){
      if(scc[i] == scc[v]) csum[scc[i]] += calc(w);
      else g2[scc[i]].pb({scc[v], w});
    }
  }

  int s; cin >> s;
  memset(dp, -1, sizeof dp);
  cout<< go(scc[s-1]) << el;
}