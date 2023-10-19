#include "line.cpp"
#include "circle.cpp"
#include "convex_hull.cpp"
int sgn(double x){return x<-eps?-1:x>eps;}
struct poly {
	int n, normal = -1; vector<pt> p;
	poly(){}
	poly(const vector<pt>& p): p(p), n(sz(p)){}

	double area(){
		double r=0.;
		forn(i, n) r += p[i] % p[(i+1)%n];
		return abs(r)/2; // negative if CW, positive if CCW
	}

	bool isConvex() {
    bool pos=false, neg=false;
    forn(i, n) {
      int s = p[(i+2)%n].side(p[i], p[(i+1)%n]);
      pos |= s > 0;
      neg |= s < 0;
    }
    return !(pos && neg);
  }

	pt centroid(){ // (barycenter)
		pt r(0,0); double t=0;        ///REVISAR
		forn(i,n){
			r = r+(p[i]+p[(i+1)%n])*(p[i]%p[(i+1)%n]);
			t += p[i]%p[(i+1)%n];
		}
		return r/t/3;
	}

	bool has(pt q){ /// O(n)
		forn(i, n) if(q.on_segment(p[i], p[(i+1) % n])) return true;
		int cnt = 0;
		forn(i, n){
			int j = (i+1)%n;
			int k = sgn((q - p[j]) % (p[i] - p[j]));
			int u = sgn(p[i].y - q.y), v = sgn(p[j].y - q.y);
			if(k > 0 && u < 0 && v >= 0) ++cnt;
			if(k < 0 && v < 0 && u >= 0) --cnt;
		}
		return cnt!=0;
	}
  // ------------ HAS_LOG ------------ //
	void remove_col(){ // helper 
    vector<pt> s;
    forn(i, n) if(!p[i].on_segment(p[(i-1+n) % n], p[(i+1) % n])) s.pb(p[i]);
    p.swap(s);  n = sz(p);
  }
  void normalize(){  // helper 
    remove_col();
    if(p[2].left(p[0], p[1])) reverse(all(p));
    int pi = min_element(all(p)) - p.begin();
    vector<pt> s(n);
    forn(i, n) s[i] = p[(pi+i) % n];
    p.swap(s);  n = sz(p);
  }
  bool has_log(pt q){ /// O(log(n)) only CONVEX.
    if(normal == -1) normal = 1, normalize();
    if(q.left(p[0], p[1]) || q.left(p[n-1], p[0])) return false;
    int l = 1, r = n-1;    // returns true if point on boundary
    while(l+1 < r){          // (change sign of EPS in left
      int m = (l+r) / 2;       //  to return false in such case)
      if(!q.left(p[0], p[m])) l = m;
      else r = m;
    }
    return !q.left(p[l], p[l+1]);
  }
  // ------------ FARTHEST------------ //
	pt farthest(pt v){ /// O(log(n)) only CONVEX
		if(n < 10){
			int k=0;
			for1(i,n-1) if(v*(p[i]-p[k]) > eps) k=i;
			return p[k];
		}
		if(n == sz(p)) p.pb(p[0]);
		pt a = p[1]-p[0];
		int s=0, e=n, ua=v*a>eps;
		if(!ua && v*(p[n-1]-p[0]) <= eps) return p[0];
		while(1){
			int m = (s+e)/2; pt c=p[m+1]-p[m];
			int uc = v*c> eps;
			if(!uc && v*(p[m-1]-p[m]) <= eps) return p[m];
			if(ua && (!uc||v*(p[s]-p[m]) > eps))e=m;
			else if(ua || uc || v*(p[s]-p[m]) >= -eps) s=m, a=c, ua=uc;
			else e=m;
			assert(e>s+1);
		}
	}

	poly cut(line l){   // cut CONVEX polygon by line l
		vector<pt> q;  // returns part at left of l.pq
		forn(i, n) {
			int d0 = sgn(l.side(p[i])), d1 = sgn(l.side(p[(i+1) % n]));
			if(d0 >= 0) q.pb(p[i]);
			line m(p[i], p[(i+1) % n]);
			if(d0*d1 < 0 && !(l / m)) q.pb(l ^ m);
		}
		return poly(q);
	}
	ld intercircle(circle c){ /// area of intersection with circle
		ld r = 0.;
		forn(i,n){
			int j = (i+1)%n; ld w = c.intertriangle(p[i], p[j]);
			if((p[j]-c.o)%(p[i]-c.o) > 0) r+=w;
			else r-=w;
		}
		return abs(r);
	}

	ld callipers(){ // square distance: pair of most distant points
		ld r=0;     // prereq: convex, ccw, NO COLLINEAR POINTS
		for(int i=0,j=n<2?0:1; i<j; ++i){
			for(;;j=(j+1)%n){
				r = max(r,(p[i]-p[j]).norm2());
				if((p[(i+1)%n]-p[i])%(p[(j+1)%n]-p[j]) <= eps) break;
			}
		}
		return r;
	}
};

// / max_dist between 2 points (pa, pb) of 2 Convex polygons (a, b)
ld rotating_callipers(vector<pt>& a, vector<pt>& b){
  pair<ll, int> start = {-1, -1};
  if(sz(a) == 1) swap(a, b);
  forn(i, sz(a)) start = max(start, {(b[0] - a[i]).norm2(), i});
  if(sz(b) == 1) return start.fi;

  ld r = 0;
  for(int i = 0, j = start.se; i<sz(b); ++i){
    for(;; j = (j+1) % sz(a)){
      r = max(r, (b[i] - a[j]).norm2());
      if((b[(i+1) % sz(b)] - b[i]) % (a[(j+1) % sz(a)] - a[j]) <= eps) break;
    }
  }
  return r;
}
