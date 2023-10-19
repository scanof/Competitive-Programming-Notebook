#include "../c++/template.cpp"
vi X, Y;
ld Z; 
int n, m;
vd b, c;  // Cantidades, costos
vector<vd> a;  // Variables, restricciones
void pivot(int x, int y){
  swap(X[y], Y[x]);
  b[x] /= a[x][y];
  forn(j, m) if(j != y) a[x][j] /= a[x][y];
  a[x][y] = 1 / a[x][y];
  forn(i, n) if(i != x && abs(a[i][y]) > eps){
    b[i] -= a[i][y] * b[x];
    forn(j, m) if(j != y) a[i][j] -= a[i][y] * a[x][j];
    a[i][y] = -a[i][y] * a[x][y];
  }
  Z += c[y] * b[x];
  forn(j, m) if(j != y) c[j] -= c[y] * a[x][j];
  c[y] = -c[y] * a[x][y];
}

pair<ld, vd> simplex(){  // maximizar Z = c * x dado ax <= b, x_i >= 0
  X.resize(m),  iota(all(X), 0);
  Y.resize(n),  iota(all(Y), m);
  while(1){
    int x = min_element(all(b)) - b.begin(), y = -1;
    if(b[x] > -eps) break; 
    forn(j, m) if(a[x][j] < -eps){ y = j; break; }
    if(y == -1) return {-1, {}}; // no solution to Ax<=b
    pivot(x, y);
  }
  while(1){
    int x = -1, y = max_element(all(c)) - c.begin();
    if(c[y] < eps) break; 
    ld mn = inf;
    forn(i, n) if(a[i][y] > eps && b[i] / a[i][y] < mn) mn = b[i] / a[i][y], x = i;
    if(x == -1) return {inf, {}};   // c^T x is unbounded
    pivot(x, y);
  }
  vd ans(m);
  forn(i, n) if(Y[i] < m) ans[Y[i]] = b[i];
  return {Z, ans};
}