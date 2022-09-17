int cnt[nax], depth[nax], f[nax], dist[25][nax];
vi g[nax];
int dfs(int u, int dep = -1, bool flag = 0, int dis = 0, int p = -1) {
  cnt[u] = 1;
  if(flag) dist[dep][u] = dis;
  for (int v : g[u])
    if (!depth[v] && v != p) cnt[u] += dfs(v, dep, flag, dis + 1, u);
  return cnt[u];
}
int get_centroid (int u, int r, int p = -1) {
  for (int v : g[u])
    if (!depth[v] && v != p && cnt[v] > r)
      return get_centroid(v, r, u);
  return u;
}
int decompose(int u, int d = 1) {
  int centroid = get_centroid(u, dfs(u)>>1);
  depth[centroid] = d;
  dfs(centroid, d); /// if distances is needed
  for (int v : g[centroid])
    if (!depth[v])
      f[decompose(v, d + 1)] = centroid;
  return centroid;
}
int lca (int u, int v) {
  for (; u != v; u = f[u])
    if (depth[v] > depth[u])
      swap(u, v);
  return u;
}
int get_dist(int u, int v){
  int dep_l = depth[lca(u,v)];
  return dist[dep_l][u] + dist[dep_l][v];
}
