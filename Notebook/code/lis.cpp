// Complejidad n log n
int lis(vector<int> const& a) {
  int n = a.size();
  vector<int> d(n+1, inf);
  d[0] = -inf;

  for (int i = 0; i < n; i++) {
    int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
    if (d[j-1] < a[i] && a[i] < d[j])
      d[j] = a[i];
  }

  int ans = 0;
  for (int i = 0; i <= n; i++) {
    if (d[i] < inf)
      ans = i;
  }
  return ans;
}
