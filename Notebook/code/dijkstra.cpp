// O ((V+E)*log V)
vector <ii> g[nax];
int d[nax], p[nax];
void dijkstra(int s, int n){
  forn(i,n) d[i] = inf, p[i] = -1;
  priority_queue < ii, vector <ii>,greater<ii> > q;
  d[s] = 0;
  q.push(ii(0, s));
  int dist, u, v, w;
  while(sz(q)){
    tie(dist, u) = q.top();
    q.pop();
    if (dist > d[u]) continue;
    for (ii e: g[u]){
      tie(v,w) = e;
      if (d[u] + w < d[v]){
        d[v] = d[u] + w;
        p[v] = u;
        q.push(ii(d[v], v));
      }
    }
  }
}
vi find_path(int t){
  vi path;
  int cur = t;
  while(cur != -1){
    path.pb(cur);
    cur = p[cur];
  }
  reverse(all(path));
  return path;
}
