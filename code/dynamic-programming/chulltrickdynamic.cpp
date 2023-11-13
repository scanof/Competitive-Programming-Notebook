typedef ll T;
const T is_query = -(1LL << 62);
struct line {
	T m, b;
	mutable multiset<line>::iterator it, end;
	const line *succ(multiset<line>::iterator it)const {
		return (++it == end ? nullptr : &*it);
	}
	bool operator < (const line &l) const {
		if(l.b != is_query) return m < l.m;
		auto s = succ(it);
		if(!s) return 0;
		return b - s->b < ld(s->m - m) * l.m;
	}
};
struct CHT : public multiset<line> {
	iterator nex(iterator y){ return ++y; }
	iterator pre(iterator y){ return --y; }
	bool bad(iterator y) {
		auto z = nex(y);
		if(y == begin()) {
			if(z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = pre(y);
		if(z == end()) return y->m == x->m && y->b == x->b;
		return ld(x->b - y->b)*(z->m - y->m) >= ld(y->b - z->b)*(y->m - x->m);
	}
	void add(T m, T b) {
		auto y = insert(line{m, b});
		y->it = y,  y->end = end();
		if(bad(y)){ erase(y);  return; }
		while(nex(y) != end() && bad(nex(y))) erase(nex(y));
		while(y != begin() && bad(pre(y))) erase(pre(y));
	}
	T eval(T x) { /// max
		line l = *lower_bound(line{x, is_query});
		return l.m*x + l.b;
	}
};
