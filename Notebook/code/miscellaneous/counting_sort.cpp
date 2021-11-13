const int nax = 3e7;
const int inf = 1e9;

void counting_sort(vector<int> &a){
  int n = sz(a);
  int maximo = *max_element(all(a));
  int minimo = *min_element(all(a));
  vector<int> cnt(maximo+1);
  forn(i,n)
    ++cnt[a[i]];
  for ( int i = 0, j = 0; i <= maximo; ++i )
    while ( cnt[i]-- )
      a[j++] = i;
}
