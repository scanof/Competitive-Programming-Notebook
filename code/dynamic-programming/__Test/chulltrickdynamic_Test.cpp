// https://codeforces.com/gym/104252/problem/B
#include <bits/stdc++.h>
using namespace std;

#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout<< #x<< " " << x<<el
#define forn(i,n) for(int i = 0; i < n; ++i)
#define for1(i,n) for(int i = 1; i <= n; ++i)
#define fore(i,l,r) for(int i = l; i <= r; ++i)
#define fored(i,l,r) for(int i = r; i >= l; --i)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

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


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  typedef pair<ll, ll> pt;
  #define x first
  #define y second
  
  int n, m; cin >> n;
  vector<pt> pts(n);
  forn(i, n) cin >> pts[i].x >> pts[i].y;

  cin >> m;
  vii lin(m); // {m, b}
  forn(i, m) cin >> lin[i].fi >> lin[i].se;

  set<int> ans[m+1];
  vi que[m], l(n, -1), r(n, m);
  int queries = n;
  while(queries){
    forn(i, n){
      if(l[i]+1 == r[i]) continue;
      que[(l[i] + r[i]) >> 1].pb(i);
    }
    CHT chull;
    forn(mid, m){
      chull.add(lin[mid].fi, lin[mid].se);
      for(int i : que[mid]){
        if(chull.eval(pts[i].x) <= pts[i].y) l[i] = mid;
        else r[i] = mid;
        if(l[i]+1 == r[i]) ans[r[i]].insert(i), --queries;
      }
      que[mid].clear();
    }
  }

  forn(i, m){
    cout << sz(ans[i]) << " ";
    for(int idx: ans[i]) cout << idx+1 << " ";
    cout << el;
  }
}