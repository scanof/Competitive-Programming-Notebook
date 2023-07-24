struct dsu {
	vi p, r, c;  int comp;
	dsu(int n):comp(n), p(n), r(n, 1){ iota(all(p), 0);}
	int find_set(int x){return x == p[x] ? x : find_set(p[x]);}
	bool union_set(int x, int y){
		if((x = find_set(x)) == (y = find_set(y))) return false;
		if(r[x] > r[y]) swap(x, y);
    r[y] += r[x];  c.pb(x);
		p[x] = y;  --comp;  
		return true;
	}
	void rollback(int snap){
		while(sz(c) > snap){
			int x = c.back(); c.pop_back();
			r[p[x]] -= r[x];  p[x] = x;  ++comp;
		}
	}
};
enum {ADD, DEL, QUERY};
struct Query {int type, x, y;};

struct DynCon {
	vector<Query> q; 
	dsu uf;  vi mt;
  map<ii, int> prv;
	DynCon(int n): uf(n){}
	void add(int x, int y){
		if(x > y) swap(x, y);
		q.pb({ADD, x, y}); mt.pb(-1);
    prv[{x, y}] = sz(q)-1;
	}
	void remove(int x, int y){
		if(x > y) swap(x, y);
		q.pb({DEL, x, y});
		int pr = prv[{x, y}];
		mt[pr] = sz(q)-1;  mt.pb(pr);
	}
	void query(){ q.pb({QUERY, -1, -1});  mt.pb(-1);}
	void process(){ // answers all queries in order
		if(!sz(q)) return;
		forn(i, sz(q)) 
      if(q[i].type == ADD && mt[i] < 0) mt[i] = sz(q);
		go(0, sz(q));
	}
	void go(int s, int e){
		if(s+1 == e){
			if(q[s].type == QUERY) cout << uf.comp << el;
			return;
		}
		int k = sz(uf.c), m = (s+e)/2;
		for(int i = e-1; i >= m; --i)
      if(mt[i] >= 0 && mt[i] < s) uf.union_set(q[i].x, q[i].y);
		go(s, m);
		uf.rollback(k);
		for(int i = m-1; i >= s; --i)
      if(mt[i] >= e) uf.union_set(q[i].x, q[i].y);
		go(m, e);
		uf.rollback(k);
	}
};