///Complexity O(V^2 * E^2)
const ll inf = 1e18;
struct edge {
  int to, rev; ll f, cap, cost;
  edge(int to, int rev, ll cap, ll cost, ll f=0) : to(to), rev(rev), cap(cap), cost(cost), f(f) {}
};
struct MCMF{
  int n;
  vector<vector<edge>> g;
  void addEdge(int s, int t, ll cap, ll cost){
    g[s].pb(edge(t, sz(g[t]), cap, cost));
    g[t].pb(edge(s, sz(g[s])-1, 0, -cost));
  }
  MCMF(int n):n(n){
    g.resize(n);
  }
  void spfa(int v0, vector<ll>& d, vector<int>& p) {
    d.assign(n, inf); d[v0] = 0;
    vector<bool> inq(n,false);
    queue<int> q;
    q.push(v0);
    p.assign(n,-1);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;
      for(int i= 0; i< g[u].size(); ++i){
        edge v = g[u][i];
        if (v.cap - v.f > 0 && d[v.to] > d[u] + v.cost ) {
          d[v.to] = d[u] + v.cost;
          p[v.to] = v.rev;
          if (!inq[v.to]) {
            inq[v.to] = true;
            q.push(v.to);
          }
        }
      }
    }
  }
  ll min_cost_flow(ll K, int s, int t) {
    ll flow = 0, cost = 0;
    vector<int> p;
    vector<ll> d;
    while (flow < K) {
      spfa(s, d, p);
      if (d[t] == inf) break;
//       find max flow on that path
      ll f = K - flow;
      int cur = t;
      while (cur != s) {
        int u = g[cur][p[cur]].to;
        int rev = g[cur][p[cur]].rev;
        ll c = g[u][rev].cap - g[u][rev].f;
        f = min(f, c);
        cur = u;
      }
      // apply flow
      flow += f;
      cost += f * d[t];
      cur = t;
      while (cur != s) {
        int rev = g[cur][p[cur]].rev;
        int u = g[cur][p[cur]].to;
        g[u][rev].f += f;
        g[cur][p[cur]].f -= f;
        cur = u;
      }
    }
    if(flow< K) return -1;
    return cost;
  }
};
