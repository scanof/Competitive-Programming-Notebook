struct fwtree{ // 0-indexed
  int n;  vi bit;
  fwtree(int n): n(n), bit(n+1){}
  int rsq(int r){ // [0, r]
    int sum = 0;
    for(++r; r; r -= r & -r) sum += bit[r];
    return sum;
  }
  int rsq(int l, int r){return rsq(r) - (l==0 ? 0 : rsq(l-1));}
  void upd(int r, int v){
    for(++r; r <= n; r += r & -r) bit[r] += v;
  }
};