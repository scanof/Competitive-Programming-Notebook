// https://codeforces.com/problemset/problem/235/C
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
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
  array<int, 26> to; 
};

const int N = 2e6+1; // el doble del MAXN
node st[N];
int sz, last, cnt[N], seen[N], idx; 
// cnt[V] = sz(end_pos[V]) : # occ de substrs de nodo V en S
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[last = sz = 0].link = -1;
    for(char c: s) extend(c);
    calc_cnt(); // si se necesita
  }
  void extend(char ch) {
    int v = ++sz, p = last, c = ch - 'a';
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
    cnt[last = v] = 1;
  }
  void calc_cnt(){
    vi ord(sz);  iota(all(ord), 1); // La raiz es el 0
    sort(all(ord), [&](int u, int v){ return st[u].len > st[v].len; } );
    for(int v: ord) cnt[st[v].link] += cnt[v]; 
  }
  int cyclic(string& t){
    int n = sz(t), v = 0, l = 0, ans = 0;
    t += t;
    forn(i, sz(t)){
      int c = t[i] - 'a';
      while(v && !st[v].to[c]) v = st[v].link, l = st[v].len;
      if(st[v].to[c]) v = st[v].to[c], ++l;
      if(i >= n){
        if(v && st[st[v].link].len >= n) v = st[v].link, l = st[v].len;
        if(seen[v] < idx && l >= n) seen[v] = idx, ans += cnt[v]; // Match
      }
    }
    return ans;
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s; cin >> s;
  suf_aut sa(s);
  int q; cin >> q;
  forn(i, q){
    string t; cin >> t;
    ++idx;
    cout<< sa.cyclic(t) << el;
  }
}