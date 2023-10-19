// https://www.spoj.com/problems/MINMOVE/
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
const int N = 4e5 + 10; // el doble del MAXN
node st[N];
int sz, last, fi_pos[N]; 
// cnt[V] = sz(end_pos[V]) : # occ de substrs de nodo V en S
struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz+1) st[i] = node();
    st[last = sz = 0].link = -1;
    for(char c: s) extend(c);
  }
  void extend(char ch) {
    int v = ++sz, p = last, c = ch - 'a';
    st[v].len = st[p].len + 1;
    fi_pos[v] = st[p].len;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p != -1) {
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else {
        int w = ++sz;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        fi_pos[w] = fi_pos[q];
        while(p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    last = v;
  }

  int first_occ(int n){
    int v = 0;
    while(n--){
      for(int& u: st[v].to) 
        if(u){ v = u; break; }
    }
    return fi_pos[v];
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s; cin >> s;
  s += s;
  suf_aut sa(s);
  
  cout << sa.first_occ(sz(s)/2) - sz(s)/2 + 1 << el;
}