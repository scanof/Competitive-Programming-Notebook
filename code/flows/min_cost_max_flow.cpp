const ll inf = 1e18;
struct edge{
  int to, rev; ll cap, cos, f{0};
  edge(int to, int rev, ll cap, ll cos):to(to), rev(rev), cap(cap), cos(cos){}
};
struct MCMF{
  int n, s, t; 
  vector<vector<edge>> g;
  vi p;  vll dis;
  MCMF(int n): n(n), g(n){}
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