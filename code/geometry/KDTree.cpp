struct pt{
	ld x, y;
	pt(){}
	pt(ld x, ld y): x(x), y(y){}
  pt operator+(pt p){ return pt(x+p.x, y+p.y); }
	pt operator-(pt p){ return pt(x-p.x, y-p.y); }
	ld operator*(pt p){ return x*p.x + y*p.y; }
	ld norm2(){ return *this * *this; }
	bool operator<(pt p)const{ // for sort, convex hull/set/map
		return x < p.x - eps || (abs(x - p.x) <= eps && y < p.y - eps); }
};
inline bool onx(pt a, pt b){ return a.x < b.x; }
inline bool ony(pt a, pt b){ return a.y < b.y; }
// Given a set of N points, answer queries of nearest point in O(log(N))
struct Node {
	pt pp;
	ll x0 = inf, x1 = -inf, y0 = inf, y1 = -inf;
	Node *fir = 0, *sec = 0;
	inline ll distance(pt p){
		ll x = min(max(x0, p.x), x1);
		ll y = min(max(y0, p.y), y1);
		return (pt(x, y) - p).norm2();
	}
	Node(vector<pt>&& vp): pp(vp[0]){
		for(pt& p: vp){
			x0 = min(x0, p.x), x1 = max(x1, p.x);
			y0 = min(y0, p.y), y1 = max(y1, p.y);
		}
		if(sz(vp) > 1){
			sort(all(vp), x1 - x0 >= y1 - y0 ? onx : ony);
			int m = sz(vp) / 2;
			fir = new Node({vp.begin(), vp.begin() + m});
			sec = new Node({vp.begin() + m, vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({all(vp)})) {}
	pair<ll, pt> search(pt p, Node *node){
		if(!node->fir){ // To avoid query point as answer: 
			// ADD:  if(p == node -> pp) return {INF, pt()};
			return {(p - node->pp).norm2(), node->pp};
		}
		Node *f = node->fir, *s = node->sec;
		ll bf = f->distance(p), bs = s->distance(p);
		if(bf > bs) swap(bf, bs), swap(f, s);
		auto best = search(p,f);
		if(bs < best.fi) best = min(best, search(p, s));
		return best;
	}
	pair<ll, pt> nearest(pt p){ return search(p, root); }
};