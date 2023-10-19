// https://codeforces.com/gym/104614/problem/L
#include <bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define forn(i,n) for(int i=0; i<n; i++)
#define fore(i,l,r) for(int i=l; i<=r; i++)
#define el '\n'
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << " : " << x << el;


typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;

const int N = 101;

const ll inf = 1e18;
struct edge{
  int to, rev; ll cap, cos, f{0};
  edge(int to, int rev, ll cap, ll cos):to(to), rev(rev), cap(cap), cos(cos){}
};
struct MCMF{
  int n, s, t; 
  vector<vector<edge>> g;
  vi p;  vll dis;
  MCMF(int n, int s, int t): n(n), s(s), t(t), g(n){}
  void addEdge(int s, int t, ll cap, ll cos){
    g[s].pb(edge(t, sz(g[t]), cap, cos));
    g[t].pb(edge(s, sz(g[s])-1, 0, -cos));
  }
  void spfa(int v0){
    dis.assign(n, inf); dis[v0] = 0;
    p.assign(n, -1);
    vector<bool> inq(n);
    queue<int> q({v0});
    while(sz(q)){
      int u = q.front(); q.pop();
      inq[u] = 0;
      for(auto&[v, rev, cap, cos, f] : g[u]){
        if(cap - f > 0 && dis[v] > dis[u] + cos){
          dis[v] = dis[u] + cos, p[v] = rev;
          if(!inq[v]) inq[v] = 1, q.push(v);
        }
      }
    }
  }
  ll min_cos_flow(ll K){
    ll flow = 0, cost = 0;
    while(flow < K){
      spfa(s);
      if(dis[t] == inf) break;
      ll f = K - flow;    
      int cur = t; // Find flow
      while(cur != s){  
        int u = g[cur][p[cur]].to, rev = g[cur][p[cur]].rev;
        f = min(f, g[u][rev].cap - g[u][rev].f);
        cur = u;
      }
      flow += f,  cost += f * dis[t],  cur = t;     // Apply flow
      while(cur != s){
        int u = g[cur][p[cur]].to, rev = g[cur][p[cur]].rev;
        g[u][rev].f += f,  g[cur][p[cur]].f -= f;
        cur = u;
      }
    }
    if(flow < K) assert(0);
    return cost;
  }
};

int n, m, cnt[N][N];
ll d[N][N];

int main(){
  ios_base:: sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cin >> n >> m;
  forn(i, n) forn(j, m) cin >> cnt[i][j];
  forn(i, n) forn(j, n) {
    cin >> d[i][j];
    if(d[i][j] == -1) d[i][j] = 1e18;
  }
  
  forn(k, n){
    forn(u, n){
      forn(v, n) {
        if(max(d[u][k], d[k][v]) == 1e18) continue;
        d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
      }
    }
  }

  MCMF dn(n + m + 2, n+m, n+m+1);
  forn(i, m) dn.addEdge(dn.s, i, 1, 0);
  forn(i, n) dn.addEdge(m+i, dn.t, 1, 0);
  forn(i, m){ // por producto
    forn(j, n){  // llevar aca
      ll cur = 0;
      forn(k, n) cur += cnt[k][i] * d[k][j];
      dn.addEdge(i, m+j, 1, cur);
    }
  }

  cout << dn.min_cos_flow(m) << el;
}