// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	if(sz(p)<3)return p;
	vector<pt> r;
	sort(all(p)); // first x, then y
	forn(i,sz(p)){ // lower hull
		while(sz(r) >=2 && r.back().left(r[sz(r)-2], p[i]))
      r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k = sz(r);
	for(int i = sz(p)-1 ; i>=0 ; --i){ // upper hull
		while(sz(r) >= k+2 && r.back().left(r[sz(r)-2], p[i]))
      r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}
