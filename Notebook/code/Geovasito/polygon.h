int sgn(double x){return x<-eps?-1:x>eps;}
struct pol {
	int n; vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n = sz(p);}

	double area(){
		double r=0.;
		forn(i,n) r += p[i]%p[(i+1)%n];
		return abs(r)/2; // negative if CW, positive if CCW
	}

	bool isConvex() {
    bool pos=false, neg=false;
    for (int i=0; i<n; i++) {
      int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
      if (o > 0) pos = true;
      if (o < 0) neg = true;
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
		forn(i,n)
      if(ln(p[i],p[(i+1)%n]).seghas(q))
        return true; //lies on a segment
		int cnt=0;
		forn(i,n){
			int j = (i+1)%n;
			int k = sgn((q-p[j])%(p[i]-p[j]));
			int u = sgn(p[i].y - q.y),v=sgn(p[j].y - q.y);
			if(k>0 && u<0 && v>=0)cnt++;
			if(k<0 && v<0 && u>=0)cnt--;
		}
		return cnt!=0;
	}

	void remove_col(){      ///for haslog
    vector<pt> s;
    forn(i, n){
      line l(p[(i-1+n)%n], p[(i+1)%n]);
      if (!l.seghas(p[i])) s.pb(p[i]);
    }
    p.swap(s);
	}

	void normalize(){ /// (call before haslog, remove collinear first)
		remove_col();
		if(p[2].left(p[0],p[1])) reverse(all(p));
		int pi = min_element(all(p)) - p.begin();
		vector<pt> s(n);
		forn(i,n) s[i] = p[(pi+i)%n];
		p.swap(s);
	}

	bool haslog(pt q){ /// O(log(n)) only CONVEX. Call normalize first
		if(q.left(p[0],p[1]) || q.left(p.back(),p[0])) return false;
		int a=1, b=sz(p)-1;    // returns true if point on boundary
		while(b-a > 1){          // (change sign of EPS in left
			int c = (a+b)/2;       //  to return false in such case)
			if(!q.left(p[0],p[c])) a=c;
			else b=c;
		}
		return !q.left(p[a],p[a+1]);
	}

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

	pol cut(ln l){   // cut CONVEX polygon by line l
		vector<pt> q;  // returns part at left of l.pq
		forn(i,n){
			int d0 = sgn(l.pq%(p[i]-l.p)), d1 = sgn(l.pq%(p[(i+1)%n]-l.p));
			if(d0 >= 0) q.pb(p[i]);
			ln m(p[i], p[(i+1)%n]);
			if(d0*d1<0 && !(l/m)) q.pb(l^m);
		}
		return pol(q);
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
// Dynamic convex hull trick
vector<pol> w;
void add(pt q){ // add(q), O(log^2(n))
	vector<pt> p = {q};
	while(sz(w) && sz(w.back().p) < 2*sz(p)){
		for(pt v: w.back().p) p.pb(v);
		w.pop_back();
	}
	w.pb(pol(chull(p)));
}
ll query(pt v){ // max(q*v:q in w), O(log^2(n))
	ll r = -inf;
	for(auto& p : w) r = max(r, p.farthest(v)*v);
	return r;
}

/// max_dist between 2 points (pa, pb) of 2 conv. polygons (a,b)
ll rot_cal(vector<pt>& a, vector<pt>& b){
  pair<ll, int> start = {-1, -1};
  if(sz(a) == 1) swap(a, b);

  forn(i, sz(a)){
    start = max(start, {(b[0] - a[i]).norm2(), i});
  }

  if(sz(b) == 1) return start.fi;

  ll r = 0;
  for(int i = 0, j = start.se; i<sz(b); ++i){
    for(;;j=(j+1)%sz(a)){
      r = max(r,(b[i]-a[j]).norm2());
      if((b[(i+1)%sz(b)]-b[i])%(a[(j+1)%sz(a)]-a[j]) <= eps) break;
    }
  }
  return r;
}
