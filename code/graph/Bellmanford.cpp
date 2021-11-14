// O(E*V) adjacency, O(V^3) matrix
vector <ii> g[nax];
int d[nax];
void bellman_ford(int s, int n){
  forn(i,n) d[i] = inf;
  d[s] = 0; int v, w;
  forn(i,n-1){
    forn(u,n){
      for(ii e : g[u]){
        tie(v,w) = e;
        d[v] = min(d[v], d[u] + w);
      }
    }
  }
  bool negcycle= false;
  forn(u,n){
    for(ii e: g[u]){
      tie(v,w) = e;
      if (d[v] > d[u] + w) negcycle = true;
    }
  }
}
