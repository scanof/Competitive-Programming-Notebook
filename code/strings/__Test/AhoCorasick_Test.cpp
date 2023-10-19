// https://codeforces.com/group/hzSLIARNBN/contest/465346/problem/H
#include <bits/stdc++.h>

#define forn(i,n) for(int i = 0; i < n; ++i)
#define for1(i,n) for(int i = 1; i <= n; ++i)
#define fore(i,l,r) for(int i = l; i <= r; ++i)
#define all(v) v.begin(),v.end()
#define el '\n'
#define sz(v) int(v.size())
#define fi first
#define se second
#define pb push_back
#define de(x) cout << #x << " : " << x << el

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;

const static int N = 10001, alpha = 26;
int to[N][alpha], fail[N], end_w[N], cnt_w[N], fail_out[N];
struct aho_corasick{
  int sz=0, words=0;
  aho_corasick(vector<string>& str){ for(string& s: str) add(s); build(); }
  inline int conv(char ch) { return  ch-'a'; }
  void add(string &s) {
    int v = 0;
    for(char c : s) {
      int i = conv(c);
      if(!to[v][i]) to[v][i] = ++sz;
      v = to[v][i];
    }
    ++cnt_w[v];
    end_w[v] = ++words;
  }
  void build() {
    queue<int> q{{0}};
    while(sz(q)) {
      int u = q.front();  q.pop();
      forn(i, alpha) {
        int v = to[u][i];
        if(!v) to[u][i] = to[ fail[u] ][i];
        else q.push(v);
        if(!u || !v) continue;
        fail[v] = to[ fail[u] ][i];
        fail_out[v] = end_w[ fail[v] ] ? fail[v] : fail_out[ fail[v] ];
        cnt_w[v] += cnt_w[ fail[v] ];
      }
    }
  }
  int match(string &s){
    int v = 0, mat = 0;
    for(char c: s) mat += cnt_w[v = to[v][conv(c)]];
    return mat;
  }
};


int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, q, mx = 0; cin >> n >> q;
  
  vector<string> st(n);
  forn(i, n) {
    cin >> st[i];
    mx = max(mx, sz(st[i]));
  }
  aho_corasick aho(st);

  string s; cin >> s;
  int sum = aho.match(s);
  cout << sum << el;

  forn(i, q){
    int pos; cin >> pos;  --pos;
    char c; cin >> c;
    string tmp = s.substr(max(0, pos - mx + 1), mx*2);
    sum -= aho.match(tmp);
    
    s[pos] = c;
    tmp = s.substr(max(0, pos - mx + 1), mx*2);
    sum += aho.match(tmp);
    cout << sum << el;
  }
}