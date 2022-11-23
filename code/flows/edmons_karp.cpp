// Complexity O(V*E^2)
const ll inf = 1e18;

struct EKarp{
  vector<int> p;
  vector<vector<ll>> cap, flow;
  vector<vector<int>> g;
  int n, s, t;

  EKarp(int n_){
    n = n_; g.resize(n);
    cap = flow = vector<vector<ll>>(n,vector<ll>(n));
  }

  void addEdge(int u, int v, ll c){
    cap[u][v] = c;
    g[u].pb(v); g[v].pb(u);
  }

  ll bfs(int s, int t) {
    p.assign(n, -1);  p[s] = -2;
    queue<pair<int,ll>> q;
    q.push(pair<int,ll>(s, inf));
    while (!q.empty()) {
      int u = q.front().fi; ll f = q.front().se;
      q.pop();
      for(int v: g[u]){
        if (p[v] == -1 && cap[u][v] - flow[u][v]>0) {
          p[v] = u;
          ll df = min(f, cap[u][v]-flow[u][v]);
          if (v == t) return df;
          q.push(pair<int,ll>(v, df));
        }
      }
    }
    return 0;
  }
  ll maxFlow() {
    ll mf = 0;
    ll f;
    while (f = bfs(s,t)){
      mf += f;
      int v = t;
      while (v != s) {
        int prev = p[v];
        flow[v][prev] -= f;
        flow[prev][v] += f;
        v = prev;
      }
    }
    return mf;
  }
};
