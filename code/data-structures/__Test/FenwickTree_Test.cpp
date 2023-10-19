// https://codeforces.com/problemset/problem/597/C
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define el '\n'

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;

struct fwtree{ // 0-indexed
  int n;  vll bit;
  fwtree(int n): n(n), bit(n+1){}
  ll rsq(int r){ // [0, r]
    ll sum = 0;
    for(++r; r; r -= r & -r) sum += bit[r];
    return sum;
  }
  ll rsq(int l, int r){return rsq(r) - (l==0 ? 0 : rsq(l-1));}
  void upd(int r, ll v){
    for(++r; r <= n; r += r & -r) bit[r] += v;
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, k; cin >> n >> k;
  vi a(n); forn(i, n) cin >> a[i];

  vector<fwtree> ft(k+1, fwtree(n+1));
  forn(i, n){
    ft[0].upd(a[i], 1);
    for1(j, k){
      ll cur = ft[j-1].rsq(0, a[i]-1);
      ft[j].upd(a[i], cur);
    }
  }
  cout << ft[k].rsq(1, n) << el;
}