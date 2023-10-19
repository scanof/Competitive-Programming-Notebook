// https://codeforces.com/group/XrhoJtxCjm/contest/422671/problem/H
#include <bits/stdc++.h>

#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout<< #x<< " " << x<<el
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)

using namespace std;

typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

const ld pi = acos(-1), eps = 1e-8;
const int inf = 1e9, mod = 1e9+7;

const static int N = 500000 * 3, alpha = 2, B = 20;
int to[N][alpha], sz, q[500000];
vi idx[N];

inline int conv(char c){return c - '0'; }
string to_bin(int x){return bitset<B>(x).to_string(); }

inline void add(int x, int i){
  int u = 0;
  for(char ch: to_bin(x)){
    int c = conv(ch);
    if(!to[u][c]) to[u][c] = ++sz;
    u = to[u][c];
    idx[u].pb(i);
  }
}

inline void rem(int x, int i){
  int u = 0;
  for(char ch: to_bin(x)){
    int c = conv(ch);
    u = to[u][c];
    idx[u].pop_back();
  }
}

int calc(int x, int l, int r){
  int v = 0, b = B-1, ans = 0;
  for(char ch: to_bin(x)){
    int c = 1 - (conv(ch));
    int u = to[v][c];

    if(u){
      auto it = lower_bound(all(idx[u]), l);
      if(it == idx[u].end() || *it > r) u = 0;
    }

    if(!u) c = 1 - c;
    else ans += 1 << b;

    v = to[v][c];
    --b;
  }
  return ans;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout << setprecision(10) << fixed; 
  int n; cin >> n;
  int idx = 0;
  
  forn(i, n){
    int t, x; cin >> t;
    if(t == 0){
      cin >> x;
      q[idx++] = x;
      add(q[idx-1], idx);
    } else if(t == 2){
      cin >> x;
      forn(j, x){
        rem(q[idx-1], idx);
        --idx;
      }
    } else{
      int l, r;
      cin >> l >> r >> x;
      cout << (calc(x, l, r) ^ x) << el;
    }
  }
}