// Complexity O(V*E) worst, O(E) on average.
vector<ii> g[N];
ll dist[N];
int pa[N], cnt[N];
bool in_q[N];
bool spfa(int s, int n){
  forn(i, n) dist[i] = (i == s ? 0 : inf);
  queue<int> q({s});  in_q[s] = 1;
  int start = -1;
  while(sz(q) && start == -1) {
    int u = q.front();  q.pop();
    in_q[u] = 0;
    for(auto& [v, w] : g[u]){
      if(dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pa[v] = u;
        if(!in_q[v]) {
          q.push(v);
          in_q[v] = 1;
          ++cnt[v];
          if(cnt[v] > n){ start = v;  break; }
        }
      }
    }
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