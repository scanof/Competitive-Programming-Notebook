// O(E*V) list adjacency, O(V^3) matrix
vector<ii> g[nax];
int dist[nax];
void bellman_ford(int s, int n){
  forn(i,n) dist[i] = inf;
  dist[s] = 0; int v, w;
  forn(i,n-1){
    forn(u,n){
      for(ii e : g[u]){
        tie(v,w) = e;
        dist[v] = min(dist[v], dist[u] + w);
      }
    }
  }
  bool negcycle= false;
  forn(u,n){
    for(ii e: g[u]){
      tie(v,w) = e;
      if (dist[v] > dist[u] + w) negcycle = true;
    }
  }
}
