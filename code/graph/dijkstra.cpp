// O ((V+E)*log V)
vector <ii> g[nax];
int d[nax], p[nax];
void dijkstra(int s, int n){
  forn(i, n) d[i] = inf, p[i] = -1;
  d[s] = 0;
  priority_queue <ii, vector <ii>,greater<ii> > q;
  q.push({0, s});
  while(sz(q)){
    auto [dist, u] = q.top();  q.pop();
    if(dist > d[u]) continue;
    for(auto& [v, w]: g[u]){
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
