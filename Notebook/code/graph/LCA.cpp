// Implementacion con segment tree
// Complejidad: preprocesamiento O(n), queries O(log n)
struct LCA {
  vi height, euler, first, segtree;
  vector<bool> visited;
  int n;
  LCA(vector<vector<int>> &adj, int root = 0) {
    n = sz(adj);
    height.resize(n);
    first.resize(n);
    euler.reserve(n * 2);
    visited.assign(n, false);
    dfs(adj, root);
    int m = sz(euler);
    segtree.resize(m * 4);
    build(1, 0, m - 1);
  }
  void dfs(vector<vector<int>> &adj, int node, int h = 0) {
    visited[node] = true;
    height[node] = h;
    first[node] = sz(euler);
    euler.pb(node);
    for (auto to : adj[node]) {
      if (!visited[to]) {
        dfs(adj, to, h + 1);
        euler.pb(node);
      }
    }
  }
  void build(int node, int b, int e) {
    if (b == e) segtree[node] = euler[b];
    else{
      int mid = (b + e) / 2;
      build(node*2, b, mid);
      build(node*2+1, mid + 1, e);
      int l = segtree[node*2], r = segtree[node*2+1];
      segtree[node] = (height[l] < height[r]) ? l : r;
    }
  }
  int query(int node, int b, int e, int L, int R) {
    if (b > R || e < L) return -1;
    if (b >= L && e <= R) return segtree[node];
    int mid = (b + e)/2;
    int left = query(node*2, b, mid, L, R);
    int right = query(node*2+1, mid + 1, e, L, R);
    if (left == -1) return right;
    if (right == -1) return left;
    return height[left] < height[right] ? left : right;
  }
  int lca(int u, int v) {
    int left = first[u], right = first[v];
    if (left > right) swap(left, right);
    return query(1, 0, sz(euler) - 1, left, right);
  }
};
