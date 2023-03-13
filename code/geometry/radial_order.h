struct pt {
	ld x,y;
	pt(ld x, ld y):x(x),y(y){}
	pt operator-(pt p)const{return pt(x-p.x, y-p.y);}
};
struct Cmp { // IMPORTANT: add const in pt operator -
	pt r;
	Cmp(pt r):r(r){}
	int cuad(const pt &a)const {
		if(a.x>0 && a.y>=0) return 0;
		if(a.x<=0 && a.y>0) return 1;
		if(a.x<0 && a.y<=0) return 2;
		if(a.x>=0 && a.y<0) return 3;
		assert(a.x==0 && a.y==0);
		return -1;
	}
	bool cmp(const pt& p1, const pt& p2)const {
		int c1=cuad(p1), c2=cuad(p2);
		if(c1==c2) return p1.y*p2.x < p1.x*p2.y;
		return c1<c2;
	}
	bool operator()(const pt& p1, const pt& p2)const {
		return cmp(p1-r, p2-r);
	}
};
// Declare center and sort
pt center(xc, yc);
sort(all(pts), Cmp(center));
