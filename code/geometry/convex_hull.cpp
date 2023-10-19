struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  bool operator<(pt p)const{ // for sort, convex hull/set/map
		return x < p.x - eps || (abs(x - p.x) <= eps && y < p.y - eps); }
  pt operator-(pt p){return pt(x - p.x, y - p.y);}
  ld operator%(pt p){return x * p.y - y * p.x;}
  ld side(pt p, pt q){return (q - p) % (*this - p);}
};
// CCW order, excludes collinear points
// Change .side(r[sz(r)-2], p[i]) > 0 to include collinear
vector<pt> chull(vector<pt>& p){ 
  if(sz(p) < 3) return p;
  vector<pt> r;
  sort(all(p));  // first x, then y
  forn(i, sz(p)){ // lower hull
    while(sz(r) > 1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  int k = sz(r);
  fored(i, 0, sz(p)-1){ // upper hull
    while(sz(r) > k+1 && r.back().side(r[sz(r)-2], p[i]) >= 0) r.pop_back();
    r.pb(p[i]);
  }
  r.pop_back();
  return r;
}