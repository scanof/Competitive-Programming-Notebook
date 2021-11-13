struct matrix{ // define N
  int r, c, m[N][N];
  matrix(int r, int c):r(r),c(c){
    memset(m, 0, sizeof m);
  }
  matrix operator *(const matrix &b){
    matrix c = matrix(this->r, b.c);
    forn(i,this->r){
      forn(k,b.r){
        if(!m[i][k]) continue;
        forn(j,b.c){
          c.m[i][j] += m[i][k]*b.m[k][j];
        }
      }
    }
    return c;
  }
};
matrix pow(matrix &b, ll e){
  matrix c = matrix(b.r, b.c);
  forn(i,b.r) c.m[i][i] = 1;
  while(e){
    if(e&1LL) c = c*b;
    b = b*b , e/=2;
  }
  return c;
}
