#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define fore(i,l,r) for(int i=l; i <= r; ++i)
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << ": " << x <<  el;

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<int,int> ii;
typedef vector<ii> vii;

struct sqrt_decomp{
  int n, len;  vi a, b;
  sqrt_decomp(){}
  sqrt_decomp(vi& arr): n(sz(arr)), len(sqrt(n) + 1), a(arr), b(len){
    forn(i, n) b[i / len] += a[i];
  }
  void update(int pos, int val){
    b[pos / len] += val - a[pos];  // Block update
    a[pos] = val;                  // Point update
  }
  int query(int l, int r){
    int sum = 0,  b_l = l / len,  b_r = r / len;
    if(b_l == b_r) fore(i,l,r) sum += a[i]; // L, R in same block
    else{
      fore(i, l, len*(b_l+1) - 1) sum += a[i];  // Left Tail (Points)
      fore(i, len*b_r, r) sum += a[i];    // Right Tail (Points)
      fore(i, b_l+1, b_r-1) sum += b[i];  // Block query
    }
    return sum;
  }
};


int main(){
  // ios_base::sync_with_stdio(0);
  // cin.tie(0); cout.tie(0);
  vi a{1, 2, 3, 4, 5};
  d(sz(a));
  sqrt_decomp sq(a);
  cout << sq.query(0, 5) << el;
}