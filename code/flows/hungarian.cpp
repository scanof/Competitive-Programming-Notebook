// Complexity O(V^3) maximiza
const int nax = 300;
const int inf = 1e9;
struct KM {
  int W[nax][nax], n;
	int mx[nax], my[nax]; // match arr
	int lx[nax], ly[nax]; // label arrMAXN
	int x[nax], y[nax]; // used arr
	int hungary(int nd) {
    int i;
    x[nd] = 1;
    forn(i,n)
      if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
        y[i] = 1;
        if(my[i] == -1 || hungary(my[i])) {
          my[i] = nd;
          return 1;
        }
      }
    return 0;
	}
	int run() {
    int k, d;
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    forn(i,n)
      lx[i] = 0, ly[i] = 0;
    forn(i,n)
      forn(j,n)
        lx[i] = max( lx[i] ,W[i][j]);
    forn(i,n) {
      while(1) {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        if(hungary(i))  break;
        d = inf;
        forn(j,n) {
          if(x[j]) {
            forn(k,n)
              if(!y[k])
                d = min(d,lx[j]+ly[k]-W[j][k]);
          }
        }
        if(d == inf)  break;
        forn(j,n) {
          if(x[j])    lx[j] -= d;
          if(y[j])    ly[j] += d;
        }
      }
    }
    int res = 0;
    forn(i,n) {
      if(my[i] != -1)
        res += W[my[i]][i];
    }
    return res;
	}
} km;
