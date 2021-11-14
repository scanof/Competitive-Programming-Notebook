typedef ll T;
const T is_query=-(1LL<<62);
struct line {
	T m,b;
	mutable multiset<line>::iterator it,end;
	const line *succ(multiset<line>::iterator it)const {
		return (++it == end ? nullptr : &*it);
	}
	bool operator < (const line &rhs) const {
		if(rhs.b!=is_query) return m < rhs.m;
		const line *s = succ(it);
		if(!s) return 0;
		return b-s->b < (ld)(s->m-m)*rhs.m;
	}
};
struct CHT : public multiset<line> {
	bool bad(iterator y) {
		iterator z = next(y);
		if(y==begin()) {
			if(z==end())return false;
			return y->m == z->m && y->b <= z->b;
		}
		iterator x = prev(y);
		if(z == end()) return y->m==x->m&&y->b==x->b;
		return (ld)(x->b-y->b)*(z->m-y->m)>=(ld)(y->b-z->b)*(y->m-x->m);
	}
	iterator next(iterator y){return ++y;}
	iterator prev(iterator y){return --y;}
	void add(T m, T b) {
		iterator y = insert((line){m,b});
		y->it = y; y->end = end();
		if(bad(y)){ erase(y); return; }
		while(next(y)!=end() && bad(next(y))) erase(next(y));
		while(y!=begin() && bad(prev(y)))erase(prev(y));
	}
	T eval(T x) { /// max
		line l = *lower_bound((line){x,is_query});
		return l.m*x+l.b;
	}
};
