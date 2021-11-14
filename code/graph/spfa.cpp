// Complexity O(V*E) worst, O(E) on average.
vector<ii> g[nax];
bool inqueue[nax];
int n;
bool spfa(int s, vi& d) {
  d.assign(n, inf);
  vi cnt(n, 0);
  queue<int> q;
  d[s] = 0;
  q.push(s);
  inqueue[s] = true;
  int u, v, w;
  while(sz(q)) {
    u = q.front(); q.pop();
    inqueue[u] = false;
    for (ii e: g[u]) {
      tie(v, w) = e;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        if (!inqueue[v]) {
          q.push(v);
          inqueue[v] = true;
          cnt[v]++;
          if (cnt[v] > n) return false;  // negative cycle
        }
      }
    }
  }
  return true;
}
