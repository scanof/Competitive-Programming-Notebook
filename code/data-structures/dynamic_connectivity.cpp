struct dsu {
	vi p, r, c;  int comp;
	dsu(int n): p(n), r(n, 1), comp(n){iota(all(p), 0);}
	int find_set(int i){return i == p[i] ? i : find_set(p[i]);}
	void union_set(int i, int j){
		if((i = find_set(i)) == (j = find_set(j))) return;
		if(r[i] > r[j]) swap(i, j);
    r[j] += r[i];  c.pb(i);
		p[i] = j;  --comp;
	}
	void rollback(int snap){
		while(sz(c) > snap){
			int x = c.back(); c.pop_back();
			r[p[x]] -= r[x];  p[x] = x;  ++comp;
		}
	}
};
enum {ADD, DEL, QUERY};
struct Query {int type, u, v;};
struct DynCon {
	vector<Query> q;  dsu uf;
	vi mt;  map<ii, int> prv;
	DynCon(int n): uf(n){}
	void add(int i, int j){
		if(i > j) swap(i, j);
		q.pb({ADD, i, j}); mt.pb(-1);
    prv[{i, j}] = sz(q)-1;
	}
	void remove(int i, int j){
		if(i > j) swap(i, j);
		q.pb({DEL, i, j});
		int pr = prv[{i, j}];
		mt[pr] = sz(q)-1;  mt.pb(pr);
	}
	void query(){ q.pb({QUERY, -1, -1});  mt.pb(-1);}
	void process(){ // answers all queries in order
		if(!sz(q)) return;
		forn(i, sz(q)) if(q[i].type == ADD && mt[i] < 0) mt[i] = sz(q);
		go(0, sz(q));
	}
	void go(int s, int e){
		if(s+1 == e){
			if(q[s].type == QUERY) cout << uf.comp << el;
			return;
		}
		int k = sz(uf.c), m = (s+e)/2;
		fored(i, m, e-1) if(mt[i] >= 0 && mt[i] < s) uf.union_set(q[i].u, q[i].v);
		go(s, m);  uf.rollback(k);
    fored(i, s, m-1) if(mt[i] >= e) uf.union_set(q[i].u, q[i].v);
		go(m, e);  uf.rollback(k);
	}
};