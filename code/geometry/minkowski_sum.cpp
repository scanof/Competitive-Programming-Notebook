struct pt{
  ld x, y;
  pt(){}
  pt(ld x, ld y): x(x), y(y){}
  pt operator+(pt p){return pt(x + p.x, y + p.y);}
  pt operator-(pt p){return pt(x - p.x, y - p.y);}
  ld operator%(pt p){return x * p.y - y * p.x;}
  ld side(pt p, pt q){return (q - p) % (*this - p);}
};

struct mink_sum{
  vector<pt> p, q, pol;
  mink_sum(){}
  mink_sum(vector<pt>& p1, vector<pt>& p2, bool inter = 1): p(p1), q(p2){
    if(inter) for(auto& [x, y] : q) x = -x, y = -y;
    pol.reserve(sz(p) + sz(q));
    reorder(p),  reorder(q);
    forn(i, 2) p.pb(p[i]), q.pb(q[i]);
	  int i = 0, j = 0;
    while(i+2 < sz(p) || j+2 < sz(q)){
      pol.pb(p[i] + q[j]);
      auto cro = (p[i+1] - p[i]) % (q[j+1] - q[j]);
      i += cro >= -eps;
      j += cro <= eps;
    }
  }
  void reorder(vector<pt> &p){
    if(p[2].side(p[0], p[1]) < 0) reverse(all(p));
    int pos = 0;
    forn(i, sz(p)) if(ii{p[i].y, p[i].x} < ii{p[pos].y, p[pos].x}) pos = i;
    rotate(p.begin(), p.begin() + pos, p.end());
  }
  bool has(pt p){
    int cnt = 0;
    forn(i, sz(pol)) cnt += p.side(pol[i], pol[(i+1) % sz(pol)]) >= 0;
    return cnt == sz(pol);
  }
  bool intersect(pt shift = pt(0, 0)){ return has(shift); }
};  // Do polygons p1 and p2+shift intersect?