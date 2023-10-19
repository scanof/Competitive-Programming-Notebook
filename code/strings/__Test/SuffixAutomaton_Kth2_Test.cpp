// https://codeforces.com/contest/128/problem/B
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
int sz, last, occ[N]; 
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[sz = last = 0].link = -1;
    for(char c: s) extend(c);
    calc_occ(); // si se necesita
  }
  void extend(char c) {
    int v = ++sz, p = last;
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p != -1) {
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else{
        int w = ++sz;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        while (p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    occ[last = v] = 1;
  }
  void calc_occ(){ // occ[V] = sz(end_pos[V]) : # occ de substrs de V en S
    vi ord(sz);  iota(all(ord), 1);
    sort(all(ord), [&](int i, int j){ return st[i].len > st[j].len; } );
    for(int v: ord) occ[st[v].link] += occ[v]; 
  }
  string kth(int k){
    string s="";
    if(build(0, k, s)) return s;
    return "No such line.";
  }
  bool build(int v, int& k, string& s){
    if(v){
      if(occ[v] >= k) return 1;
      k -= occ[v];
    }
    for(auto&[c, u]: st[v].to){
      s.pb(c);
      if(build(u, k, s)) return 1;
      s.pop_back();
    }
    return 0;
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s; cin >> s;
  suf_aut sa(s);
  int k; cin >> k;
  cout << sa.kth(k) << el;
}