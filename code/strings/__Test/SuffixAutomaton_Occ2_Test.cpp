// https://codeforces.com/contest/452/problem/E
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define fored(i,l,r) for(int i=r; i>=l; --i)
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout << #x << " : " << x << el;

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

const int mod = 1e9+7;

inline int add(int a, int b){return a+b >= mod ? a+b-mod : a+b;}
inline int sub(int a, int b){return a-b >= 0 ? a-b : a-b+mod;}

struct node { 
  int len, link;
  array<int, 27> to; 
};
const int N = 6e5 + 10; // el doble del MAXN
node st[N];
int sz, last, occ[N][3], dp[N], ans[N]; 
// occ[V] = sz(end_pos[V]) : # ocurrencias de substrs de nodo V en S
struct suf_aut{
  suf_aut(){ 
    forn(i, sz+1) st[i] = node();
    st[last = sz = 0].link = -1;
    // for(char c: s) extend(c);
  }
  void extend(char ch, int idx) {
    int v = ++sz, p = last, c = ch == '#' ? 26 : ch - 'a';
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p != -1){
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else {
        int w = ++sz;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        while(p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    occ[last = v][idx] = 1;
  }
  void calc_occ(){ // occ[V] = sz(end_pos[V]) : # occ de substrs de V en S
    vi ord(sz);  iota(all(ord), 1);
    sort(all(ord), [&](int i, int j){ return st[i].len > st[j].len; } );
    forn(idx, 3) for(int v: ord) occ[st[v].link][idx] += occ[v][idx]; 
  }

  void dfs(int v){
    if(dp[v] != -1) return;

    dp[v] = 1;
    forn(i, 3) dp[v] = ll(dp[v]) * occ[v][i] % mod;

    if(dp[v] && v){
      int mn_len = st[st[v].link].len + 1, mx_len = st[v].len;
      ans[mn_len] = add(ans[mn_len], dp[v]);
      ans[mx_len + 1] = sub(ans[mx_len + 1], dp[v]);
    }
    forn(i, 26) if(st[v].to[i]) dfs(st[v].to[i]);
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  suf_aut sa;
  int mn = 3e5;
  forn(i, 3){
    string s; cin >> s;
    mn = min(mn, sz(s));
    for(char c: s) sa.extend(c, i);
    sa.extend('#', i);
  }
  sa.calc_occ();
  memset(dp, -1, sizeof dp);
  sa.dfs(0);

  int sum = 0;
  for1(i, mn) {
    sum = add(sum, ans[i]);
    cout << sum << " ";
  }
  cout << el;
}