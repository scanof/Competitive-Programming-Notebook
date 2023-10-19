/// https://codeforces.com/gym/100402/attachments  (C)
#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define allr(v) v.rbegin(),v.rend()

using namespace std;

typedef long long ld;
typedef long long ll;
typedef vector<int> vi;

const ll inf = 1e18;
const double pi = acos(-1), eps = 0;

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

typedef pair<pt, int> pti;
vector<pti> solve(vector<pti> &vp){
  if(sz(vp) <= 1) return vp;
  
  int mid = sz(vp) / 2;
  auto lef = vector<pti>(vp.begin(), vp.begin() + mid);
  lef = solve(lef);

  vector<pt> k;
  for(auto& a: lef) k.pb(a.fi);
  KDTree kd(k);

  vector<pti> rig;
  fore(i, mid, sz(vp)-1){
    pt m = {vp[i].fi.x / 2, vp[i].fi.y / 2};
    ll dist = kd.nearest(m).fi;
    if(dist > m.norm2()) rig.pb(vp[i]);
  }

  rig = solve(rig);
  for(auto& a: rig) lef.pb(a);
  return lef;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout<< setprecision(1)<< fixed;
  freopen("nothingontv.in","r",stdin);
  freopen("nothingontv.out","w",stdout);
  int n; cin >> n;
  vector<pti> vp(n);
  forn(i, n){
    cin >> vp[i].fi.x >> vp[i].fi.y;
    vp[i].fi.x *= 2; 
    vp[i].fi.y *= 2;
    vp[i].se = i;
  }

  sort(all(vp), [&](auto& a, auto& b){
    return a.fi.norm2() < b.fi.norm2();
  });
  vp = solve(vp);
  
  sort(all(vp), [&](auto& a, auto& b){
    return a.se < b.se;
  });
  cout << sz(vp) << el;
  for(auto a: vp) cout << a.se + 1 << " ";
  cout << el;
}