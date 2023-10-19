// https://www.spoj.com/problems/SUBLEX/
#include <bits/stdc++.h>
 
#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'
#define fi first
#define se second
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
 
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
 
struct node {
  int len, link;
  map<char, int> to;
  bool terminal;
};
 
const int N = 4e5+1; // el doble del MAXN
node st[N];
int sz, dp[N], last;
// dp[V] = # de caminos / (palabras distintas) desde V
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[sz = last = 0].link = -1;
    for(char c: s) extend(c);
  }
  void extend(char c) {
    int v = ++sz, p = last;
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p == -1) st[v].link = 0;
    else{
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else {
        int w = ++sz;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        while (p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    last = v;
  }
  string kth(int k){
    paths(0);
    string s="";
    build(0, k, s);
    return s;
  }
  int paths(int v){
    if(dp[v]) return dp[v]; 
    dp[v] = 1;
    for(auto&[_, u] : st[v].to) dp[v] += paths(u);
    return dp[v];
  }
  void build(int v, int k, string& s){
    --k;
    if(k == 0) return;
    for(auto&[c, u] : st[v].to){
      if(k > dp[u]) k -= dp[u];
      else{
        s.pb(c);
        build(u, k, s);
        return;
      }
    }
  }
};  
 
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s; cin >> s;
  suf_aut sa(s);
  int q; cin >> q;
  forn(i, q){
    int k; cin >> k;
    cout << sa.kth(k+1) << el;
  }
} 