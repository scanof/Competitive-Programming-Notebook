// Complexity
// Preprocessing O(n)  query O(n/sqrt(n) + sqrt(n)) 
// Update O(1)
struct sqrt_decomp{
  vi a, b;
  int n, len;
  sqrt_decomp(vi &arr){ // preprocessing
    a = arr; n = sz(a); len = sqrt(n) + 1;
    b = vi(len);
    forn(i,n) b[i/len] += a[i];
  }
  void update(int pos, int val){
    int bpos = pos/len;
    b[bpos] += val - a[pos];
    a[pos] = val;
  }
  int query(int l, int r){
    int sum = 0;
    int c_l = l / len,   c_r = r / len;
    if (c_l == c_r){
      fore(i,l,r) sum += a[i];
    }else{
      fore(i,l,(c_l+1)*len-1) sum += a[i];
      fore(i,c_l+1,c_r-1) sum += b[i];
      fore(i,c_r*len,r) sum += a[i];
    }
    return sum;
  }
};
