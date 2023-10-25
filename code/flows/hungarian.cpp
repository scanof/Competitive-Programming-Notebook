const ld inf = 1e18; // To Maximize set "inf" to 0, and negate costs
inline bool zero(ld x){ return x == 0; } // For Integer/LL --> change to x == 0
struct Hungarian{
  int n; vector<vd> c;
  vi l, r, p, sn;  vd ds, u, v;
  Hungarian(int n): n(n), c(n, vd(n, inf)), l(n, -1), r(n, -1), p(n), sn(n), ds(n), u(n), v(n){}
  void set_cost(){ forn(i, n) forn(j, n) cin >> c[i][j]; }
	ld assign() {
    set_cost();
		forn(i, n) u[i] = *min_element(all(c[i]));
		forn(j, n){ 
      v[j] = c[0][j] - u[0]; 
      for1(i, n-1) v[j] = min(v[j], c[i][j] - u[i]);
    }
		int mat = 0;
		forn(i, n) forn(j, n) if(r[j] == -1 && zero(c[i][j] - u[i]  -v[j])){
      l[i] = j,  r[j] = i, ++mat; break;
    }
		for(; mat < n; ++mat){
      int s = 0, j = 0, i;
      while(l[s] != -1) ++s;
      forn(k, n) ds[k] = c[s][k] - u[s] - v[k];
      fill(all(p), -1),  fill(all(sn), 0);
      while(1){
        j = -1;
        forn(k, n) if(!sn[k] && (j == -1 || ds[k] < ds[j])) j = k;
        sn[j] = 1,  i = r[j];
        if(i == -1) break;
        forn(k, n) if(!sn[k]){
          auto n_ds = ds[j] + c[i][k] - u[i] - v[k];
          if(ds[k] > n_ds) ds[k] = n_ds,  p[k] = j;
        }
      }
      forn(k, n) if(k != j && sn[k]){
        auto dif = ds[k] - ds[j];
        v[k] += dif, u[r[k]] -= dif;
      } 
      u[s] += ds[j];
      while(p[j] >= 0) r[j] = r[p[j]],  l[r[j]] = j,  j = p[j];
      r[j] = s,  l[s] = j;
		}
		ld val = 0;
    forn(i, n) val += c[i][l[i]];
		return val;
	}
  void print_assignment(){ forn(i, n) cout << i+1 << " " << l[i]+1 << el; }
};