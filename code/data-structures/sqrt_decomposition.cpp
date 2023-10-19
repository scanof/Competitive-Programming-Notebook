// Complexity:      1. Preprocessing O(n) 
// 2. Update O(1)   3. Query O(n/sqrt(n) + sqrt(n))
struct sqrt_decomp{
  int n, len;  vi a, b;
  sqrt_decomp(){}
  sqrt_decomp(vi& arr): n(sz(arr)), len(sqrt(n) + 1), a(arr), b(len){
    forn(i, n) b[i / len] += a[i];
  }
  void update(int pos, int val){
    b[pos / len] += val - a[pos];  // Block update
    a[pos] = val;                  // Point update
  }
  int query(int l, int r){
    int sum = 0,  b_l = l / len,  b_r = r / len;
    if(b_l == b_r) fore(i,l,r) sum += a[i]; // L, R in same block
    else{
      fore(i, l, len*(b_l+1) - 1) sum += a[i];  // Left Tail (Points)
      fore(i, len*b_r, r) sum += a[i];    // Right Tail (Points)
      fore(i, b_l+1, b_r-1) sum += b[i];  // Block query
    }
    return sum;
  }
};