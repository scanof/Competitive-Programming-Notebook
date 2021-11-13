struct plane {
	pt a, n; // n: normal unit vector
	plane(pt a, pt b, pt c): a(a),n(((b-a)^(c-a)).unit()){}
	plane(){}
	bool has(pt p){return abs((p-a)*n) <= eps;}               ///DONE
	double angle(plane w){return acos(n*w.n);}
	double dist(pt p){return abs((p-a)*n);}                   ///DONE
	bool inter(ln l, pt& r){   //LINE-PLANE --> POINT
		double x = n*(l.p+l.pq-a), y = n*(l.p-a);
		if(abs(x-y) <= eps) return false;
		r = (l.p*x-(l.p+l.pq)*y)/(x-y);
		return true;
	}
	bool inter(plane w, ln& r){//PLANE-PLANE --> LINE
		pt nn = n^w.n;pt v = n^nn;double d = w.n*v;
		if(abs(d) <= eps) return false;
		pt p = a+v*(w.n*(w.a-a)/d);
		r = ln(p,p+nn);
		return true;
	}
	pt proj(pt p){inter(ln(p,p+n),p); return p;}              ///DONE
};
