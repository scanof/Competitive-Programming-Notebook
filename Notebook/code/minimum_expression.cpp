int minExp(string &t) {
  int i = 0, j = 1, k = 0, n = sz(t), x, y;
  while (i < n && j < n && k < n) {
    x = i+k;
    y = j+k;
    if (x >= n) x -= n;
    if (y >= n) y -= n;
    if (t[x] == t[y]) ++k;
    else if (t[x] > t[y]) {
      i = j+1 > i+k+1 ? j+1 : i+k+1;
      swap(i, j);
      k = 0;
    } else {
      j = i+1 > j+k+1 ? i+1 : j+k+1;
      k = 0;
    }
  }
  return i;
}
