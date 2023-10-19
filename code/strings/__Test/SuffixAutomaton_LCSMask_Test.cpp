// https://www.spoj.com/problems/LCS2/
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

struct node { 
  int len, link;
  array<int, 27> to; 
};
const int N = 2e6 + 30; // el doble del MAXN
node st[N];
int sz, last, occ[N], dp[N], all_mask, ans = 0; 
// occ[V] = sz(end_pos[V]) : # ocurrencias de substrs de nodo V en S
struct suf_aut{
  suf_aut(){ 
    forn(i, sz+1) st[i] = node();
    st[last = sz = 0].link = -1;
  }
  void extend(char ch, int idx) {
    int v = ++sz, p = last, c = ch == '#' ? 26 : ch - 'a';
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p != -1) {
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
    occ[last = v] = 1 << idx;
  }
  void calc_occ(){ // occ[V] = sz(end_pos[V]) : # occ de substrs de V en S
    vi ord(sz);  iota(all(ord), 1);
    sort(all(ord), [&](int i, int j){ return st[i].len > st[j].len; } );
    for(int v: ord) occ[st[v].link] |= occ[v]; 
  }

  void dfs(int v){
    if(dp[v] != -1) return;
    
    dp[v] = occ[v] == all_mask;
    if(dp[v]) ans = max(ans, st[v].len);
    
    forn(i, 26) if(st[v].to[i]) dfs(st[v].to[i]);
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  suf_aut sa;
  
  string s; int i = 0;
  while(getline(cin, s) && s != "0"){
    for(char c: s) sa.extend(c, i);
    sa.extend('#', i);
    ++i;
  }
  sa.calc_occ();

  all_mask = (1 << i) - 1;
  memset(dp, -1, sizeof dp);
  sa.dfs(0);
  cout << ans << el;
}