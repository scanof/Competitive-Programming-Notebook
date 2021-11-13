// Complexity O(V^2 * sqrt(E)) o O(V^3)
const ll inf = 1e17;
struct PushRelabel{
  struct edge {
    int to, rev; ll f, cap;
    edge(int to, int rev, ll cap, ll f = 0) : to(to), rev(rev), f(f), cap(cap) {}
  };
  void addEdge(int s, int t, ll cap){
    g[s].pb(edge(t, sz(g[t]), cap));
    g[t].pb(edge(s, sz(g[s])-1, (ll)0));
  }

  int n, s, t;
  vi height; vector<ll> excess;
  vector<vector<edge>> g;

  PushRelabel(int n_){
    n = n_; g.resize(n);
  }
  void push(int u, edge &e){
    ll d = min(excess[u], e.cap - e.f);
    edge &rev = g[e.to][e.rev];
    e.f += d;  rev.f -= d;
    excess[u] -= d;  excess[e.to] += d;
  }
  void relabel(int u){
    ll d = inf;
    for (edge e : g[u])
      if (e.cap - e.f > 0)
        d = min(d,(ll) height[e.to]);

    if (d < inf) height[u] = d + 1;
  }
  vi find_max_height_vertices(int s, int t) {
    vi max_height;
    for (int i = 0; i < n; i++)
      if (i != s && i != t && excess[i] > 0) {
        if (!max_height.empty() && height[i] > height[max_height[0]])
          max_height.clear();
        if (max_height.empty() || height[i] == height[max_height[0]])
          max_height.push_back(i);
      }
    return max_height;
  }

  ll maxFlow(){
    height.assign(n,0); excess.assign(n,0);
    ll max_flow = 0; bool pushed;
    vi current;

    height[s] = n; excess[s] = inf;
    for(edge &e: g[s])
        push(s,e);

    while(!(current = find_max_height_vertices(s,t)).empty()){
      for(int v: current){
        pushed = false;
        if(excess[v]==0) continue;
        for(edge &e : g[v]){
          if(e.cap - e.f>0 && height[v]== height[e.to]+1){
            pushed = true;
            push(v,e);
          }
        }
        if(!pushed){
          relabel(v);
          break;
        }
      }
    }
    for (edge e : g[t]){
      edge rev = g[e.to][e.rev];
      max_flow += rev.f;
    }
    return max_flow;
  }
};
