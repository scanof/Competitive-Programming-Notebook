struct circle {
	pt o; ld r;
	circle(pt o, ld r):o(o),r(r){}
	circle(pt x, pt y, pt z){o=bisec(x,y)^bisec(x,z);r=(o-x).norm();}///circumcircle
	bool has(pt p){return (o-p).norm()<=r+eps;}
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		ld d = (o - c.o).norm();
		if(d > r+c.r+eps || d+min(r,c.r)+eps < max(r,c.r)) return s;
		ld x = (d*d - c.r*c.r + r*r)/(2*d);
		ld y = sqrt(r*r - x*x);
		pt v = (c.o - o)/d;
		s.pb(o + v*x - v.rot(ccw90)*y);
		if(y>eps) s.pb(o + v*x + v.rot(ccw90)*y);
		return s;
	}
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		ld d=(p-o).norm();
		if(d-eps>r)return s;
		if(abs(d-r)<=eps){s.pb(p);return s;}
		d=sqrt(r*r-d*d);
		s.pb(p+l.pq.unit()*d);
		s.pb(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		ld d = sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
	bool in(circle c){ // non strict
		ld d = (o-c.o).norm();
		return d+r <= c.r+eps;
	}
	ld intertriangle(pt a, pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<=eps)return 0.;
		vector<pt> q = {a}, w = *this^ln(a,b);
		if(sz(w)==2) for(auto p:w) if((a-p)*(b-p)<-eps) q.pb(p);
		q.pb(b);
		if(sz(q)==4 && (q[0]-q[1])*(q[2]-q[1])>eps) swap(q[1],q[2]);
		ld s=0;
		forn(i, sz(q)-1){
			if(!has(q[i]) || !has(q[i+1])) s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};

vector<ld> intercircles(vector<circle> c){
	vector<ld> r(sz(c)+1); // r[k]: area covered by at least k circles
	forn(i,sz(c)){           // O(n^2 log n) (high constant)
		int k=1; Cmp s(c[i].o);
		vector<pair<pt,int> > p =
		{{c[i].o+pt(1,0)*c[i].r,0},{c[i].o-pt(1,0)*c[i].r,0}};
		forn(j, sz(c))if(j!=i){
			bool b0 = c[i].in(c[j]), b1=c[j].in(c[i]);
			if(b0 && (!b1||i<j))k++;
			else if(!b0 && !b1){
				auto v = c[i]^c[j];
				if(sz(v)==2){
					p.pb({v[0],1});
					p.pb({v[1],-1});
					if(s(v[1],v[0]))k++;
				}
			}
		}
		sort(p.begin(),p.end(),
			[&](pair<pt,int> a, pair<pt,int> b){return s(a.fi,b.fi);});
		forn(j,sz(p)){
			pt p0 = p[j?j-1:sz(p)-1].fi, p1 = p[j].fi;
			ld a=(p0-c[i].o).angle(p1-c[i].o);
			r[k] += (p0.x-p1.x)*(p0.y+p1.y)/2+c[i].r*c[i].r*(a-sin(a))/2;
			k+=p[j].se;
		}
	}
	return r;
}
