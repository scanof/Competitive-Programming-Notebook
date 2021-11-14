// Pair Fn and Fn+1
ii fib (int n) {
  if (n == 0)
    return {0, 1};

  ii p = fib(n >> 1);
  int c = p.fi * (2 * p.se - p.fi);
  int d = p.fi * p.fi + p.se * p.se;
  if (n & 1)
    return ii(d, c + d);
  else
    return ii(c, d);
}
