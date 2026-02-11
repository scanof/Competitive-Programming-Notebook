#include "../../template.h"

// https://www.spoj.com/problems/NSUBSTR/
struct node { 
  int len, link;
  array<int, 26> to; 
};
const int N = 4e5 + 10; // el doble del nax
node st[N];
int sz, last, occ[N], F[N]; 
// occ[V] = sz(end_pos[V]) : # ocurrencias de substrs de nodo V en S
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[last = sz = 0].link = -1;
    for(char c: s) extend(c);
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
    occ[last = v] = 1;
  }
  void calc_occ(){ // occ[V] = sz(end_pos[V]) : # occ de substrs de V en S
    vi ord(sz);  iota(all(ord), 1);
    sort(all(ord), [&](int i, int j){ return st[i].len > st[j].len; } );
    for(int v: ord) occ[st[v].link] += occ[v]; 

    for1(v, sz) F[st[v].len] = max(F[st[v].len], occ[v]);
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s; cin >> s;
  suf_aut sa(s);
  sa.calc_occ();
  for1(i, sz(s)) cout << F[i] << el;
}