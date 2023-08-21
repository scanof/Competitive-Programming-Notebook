// https://codeforces.com/contest/869/problem/E
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'

using namespace std;

typedef  long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

struct fwtree{ // 0-indexed
  int n, m;  vector<vll> bit;
  fwtree(){}
  fwtree(int n, int m): n(n), m(m), bit(n+1, vll(m+1, 0)){}
  ll sum(int x, int y) { // [0, x], [0, y]
    ll v = 0;
    for(int i = x+1; i; i -= i & -i)
      for(int j = y+1; j; j -= j & -j) v += bit[i][j];
    return v;
  }
  void add(int x, int y, ll dt) {
    for(int i = x+1; i <= n; i += i & -i)
      for(int j = y+1; j <= m; j += j & -j) bit[i][j] += dt;
  }
};

const int L = 0, R = 1<<30;
mt19937_64 rng(0);
uniform_int_distribution<int> dis(L, R);
inline int rd() { return dis(rng); }

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, m, q; cin >> n >> m >> q;
  fwtree fw(n+1, m+1);
  map<vi, int> id;
  forn(i, q){
    int t, r1, c1, r2, c2; 
    cin >>t >> r1 >> c1 >> r2 >> c2;
    if(t <= 2){
      if(t == 1) id[{r1, c1, r2, c2}] = rd();
      int val = (t == 1 ? 1 : -1) * id[{r1, c1, r2, c2}];

      fw.add(r1, c1, val);
      fw.add(r2+1, c1, -val);
      fw.add(r1, c2+1, -val);
      fw.add(r2+1, c2+1, val);
    } else{
      if(fw.sum(r1, c1) == fw.sum(r2, c2))
        cout << "Yes" << el;
      else cout << "No" << el;
    }
  }
}