// https://www.spoj.com/problems/LCS/
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i<n; ++i)
#define el '\n'
#define pb push_back
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()

using namespace std;

typedef vector<int> vi;

struct node {
  int len, link;
  map<char, int> to;
  bool terminal;
};

const int N = 4e5+1; // el doble del MAXN
node st[N];
int sz, last;
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
    if(p != -1) {
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
  int lcs(string &s){
    int v = 0, l = 0, ans = 0;
    forn(i, sz(s)){
      while(v && !st[v].to.count(s[i])) v = st[v].link, l = st[v].len;
      if(st[v].to.count(s[i])) v = st[v].to[s[i]], ++l;
      ans = max(ans, l); // LCS(S, s) ending at position i
    }
    return ans;
  }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  string s, t; cin >> s >> t;
  suf_aut sa(s);
  cout << sa.lcs(t) << el;
}