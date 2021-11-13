struct fwtree{ // 1-indexed
  vector<int> bit;
  int n;
  fwtree(int n):n(n){
    bit.assign(n + 1, 0);
  }
  int rsq(int r) {
    int sum = 0; for (; r; r -= r&-r ) sum += bit[r];
    return sum;
  }
  int rsq(int l, int r) {
    return rsq(r) - (l == 1 ? 0 : rsq(l - 1));
  }
  void upd(int r, int v) {
    for (; r <= n; r += r&-r) bit[r] += v;
  }
};
