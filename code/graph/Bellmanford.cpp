vector<ii> g[nax];
ll dist[nax];
bool bellman_ford(int s, int n){
  forn(i, n) dist[i] = inf;
  dist[s] = 0;
  forn(_, n-1){
    forn(u, n){
      if(dist[u] == inf) continue; // Unreachable
      for(auto& [v, w] : g[u])
        if(dist[u] + w < dist[v]) dist[v] = dist[u] + w, pa[v] = u;
    }
  }
  int start = -1;
  forn(u, n){
    if(dist[u] == inf) continue;  // Unreachable
    for(auto& [v, w] : g[u]) if(dist[u] + w < dist[v]) start = v;
  }
  if(start == -1) return 0;
  else{  // Si se necesita reconstruir
    forn(_, n) start = pa[start];
    vi cycle{start}; 
    int v = start;  
    while(pa[v] != start) v = pa[v], cycle.pb(v);
    cycle.pb(start); // solo si se necesita que vuelva al start
    reverse(all(cycle));
    return 1;
  }
}