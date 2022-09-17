// it suppose that every element is non-negative 
// in other case just translate to the right the elements  
void counting_sort(vi &a){ 
  int n = sz(a);
  int maximo = *max_element(all(a));
  vector<int> cnt(maximo+1);
  forn(i,n) ++cnt[a[i]];
  for(int i = 0, j = 0; i <= maximo; ++i)
    while(cnt[i]--) a[j++] = i;
}
