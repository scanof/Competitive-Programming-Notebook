// Corte minimo: vertices con dist[v]>=0 (del lado de src) VS.  dist[v]==-1 (del lado del dst)
// Para el caso de la red de Bipartite Matching (Sean V1 y V2 los conjuntos mas proximos a src y dst respectivamente):
// Reconstruir matching: para todo v1 en V1 ver las aristas a vertices de V2 con it->f>0, es arista del Matching
// Min Vertex Cover: vertices de V1 con dist[v]==-1 + vertices de V2 con dist[v]>0
// Max Independent Set: tomar los vertices NO tomados por el Min Vertex Cover
// Max Clique: construir la red de G complemento (debe ser bipartito!) y encontrar un Max Independet Set
// Min Edge Cover: tomar las aristas del matching + para todo vertices no cubierto hasta el momento, tomar cualquier arista de el

// Complexity O(V^2*E)
const ll inf = 1e18;

struct Dinic{
  struct edge {
    int to, rev; ll f, cap;
    edge(int to, int rev, ll cap, ll f=0) : to(to), rev(rev), f(f), cap(cap) {}
  };
  vector<vector<edge>> g;
  vector<int> q, dist, work;
  int n, s, t;

  Dinic(int n_){
    n = n_; g.resize(n);
    q.resize(n);
  }

  void addEdge(int s, int t, ll cap){
      g[s].pb(edge(t, sz(g[t]), cap));
      g[t].pb(edge(s, sz(g[s])-1, 0));
  }

  bool bfs(){
    dist.assign(n,-1), dist[s]=0;
    int qt=0;
    q[qt++]=s;
    for(int qh=0; qh<qt; ++qh){
      int u =q[qh];
      for(edge e: g[u]){
        int v=e.to;
        if(dist[v]<0 && e.f < e.cap)
          dist[v]=dist[u]+1, q[qt++]=v;
      }
    }
    return dist[t]>=0;
  }

  ll dfs(int u, ll f){
    if(u==t) return f;
    for(int &i=work[u]; i<sz(g[u]); ++i){
      edge &e = g[u][i];
      if(e.cap<=e.f) continue;
      int v=e.to;
      if(dist[v]==dist[u]+1){
        ll df=dfs(v, min(f, e.cap-e.f));
        if(df>0){
          e.f+=df, g[v][e.rev].f-= df;
          return df;
        }
      }
    }
    return 0;
  }

  ll maxFlow(int s_, int t_){
    s = s_, t = t_;
    ll max_flow=0;
    while(bfs()){
      work.assign(n,0);
      while(ll delta=dfs(s,inf))
        max_flow+=delta;
    }
    // todos los nodos con dist[u]!=-1 vs los que tienen dist[v]==-1 forman el min-cut, (u,v)
    return max_flow;
  }

  vector<ii> cut;
  vector<bool> seen;
  void dfs_cut(int u){
    seen[u] = 1;
    for(edge &e : g[u]){
      if(!seen[e.to]){
        if(dist[e.to]==-1 && e.cap!=0){
          cut.pb({u,e.to});
        }else if(e.f < e.cap){
          dfs_cut(e.to);
        }
      }
    }
  }
  vector<ii> min_cut(){
    seen.assign(n, false);
    dfs_cut(s);
    sort(all(cut));
    cut.resize(unique(all(cut)) - cut.begin());
    return cut;  
  }
};
