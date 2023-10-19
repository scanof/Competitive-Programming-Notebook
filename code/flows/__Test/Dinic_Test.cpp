// https://codeforces.com/gym/104467/problem/H
#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define fore(i,l,r) for(int i=l; i<=r; ++i)
#define pb push_back
#define el '\n'
#define d(x) cerr<< #x<< " " << x<<el
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define allr(v) v.rbegin(),v.rend()
using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<ll, int, int, ll> i4;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int N = 1e5 + 10;
const ll inf = 1e18;

vector<ll> dist[N];
int n, m, P, Q, h;
vector<ii> g[N];

void dij(int s){
  dist[s] = vector<ll>(n, inf);
  priority_queue<pair<ll, int>> q;
  dist[s][s] = 0;
  q.push({0, s});

  while(sz(q)){
    auto [di, u] = q.top(); q.pop();
    if(dist[s][u] < -di) continue;

    for(auto&[v, w] : g[u]){
      if(dist[s][v] > dist[s][u] + w){
        dist[s][v] = dist[s][u] + w;
        q.push({-dist[s][v], v});
      }
    }
  }
}
struct edge {
  int to, rev; ll cap, f{0};
  edge(int to, int rev, ll cap): to(to), rev(rev), cap(cap){}
};
struct Dinic{
  int n, s, t; ll max_flow = 0;
  vector<vector<edge>> g;
  vi q, dis, work;
  Dinic(int n, int s, int t): n(n), s(s), t(t), g(n), q(n){}
  void addEdge(int s, int t, ll cap){
    g[s].pb(edge(t, sz(g[t]), cap));
    g[t].pb(edge(s, sz(g[s])-1, 0));
  }
  
  bool bfs(){
    dis.assign(n, -1), dis[s] = 0;
    int qt = 0;
    q[qt++] = s;
    forn(qh, qt){
      int u = q[qh];
      for(auto& [v, _, cap, f]: g[u])
        if(dis[v] < 0 && f < cap) dis[v] = dis[u] + 1, q[qt++] = v;
    }
    return dis[t] >= 0;
  }
  ll dfs(int u, ll cur){
    if(u == t) return cur;
    for(int& i = work[u]; i < sz(g[u]); ++i){
      auto& [v, rev, cap, f] = g[u][i];
      if(cap <= f) continue;
      if(dis[v] == dis[u] + 1){
        ll df = dfs(v, min(cur, cap - f));
        if(df > 0){
          f += df, g[v][rev].f -= df;
          return df;
        }
      }
    }
    return 0;
  }
  ll maxFlow(){
    ll cur_flow = 0;
    while(bfs()){
      work.assign(n, 0);
      while(ll delta = dfs(s, inf)) cur_flow += delta;
    }
    max_flow += cur_flow;
    // todos los nodos con dis[u]!=-1 vs los que tienen dis[v]==-1 forman el min-cut, (u,v)
    return max_flow; 
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(20)<< fixed;
  cin >> n >> m >> P >> Q;
  forn(i, m){
    int u, v, w; cin >> u >> v >> w;
    g[--u].pb({--v, w});
  }
  vector<ii> p(P), q(Q);
  forn(i, P){
    int v, x; cin >> v >> x;
    dij(--v);
    p[i] = {v, x};
  }
  ll tot=0;
  forn(i, Q) cin >> q[i].fi >> q[i].se, --q[i].fi, tot += q[i].se;
  cin >> h;  dij(--h);
  Dinic dn(P + Q + 3, P + Q + 1, P + Q + 2);

  vector<i4> edges;
  dn.addEdge(dn.s, 0, inf);
  forn(i, Q){
    auto [v, x] = q[i];
    edges.pb({dist[h][v] * 2, 0, P + 1 + i, inf});
  }
  forn(i, P){
    auto [u, xu] = p[i];
    dn.addEdge(dn.s, i+1, xu);
    forn(j, Q){
      auto [v, xv] = q[j];
      if(i == 0)  dn.addEdge(P + 1 + j, dn.t, xv);
      edges.pb({dist[u][v], i+1, P + 1 + j, inf});
    }
  }
  sort(all(edges));

  ll ans = -1;
  for(auto& ed : edges){
    auto [t, u, v, cap] = ed;
    if(t >= inf) break;
    dn.addEdge(u, v, cap);
    if(dn.maxFlow() == tot) {
      ans = t;
      break;
    }
  }
  cout << ans << el;
}