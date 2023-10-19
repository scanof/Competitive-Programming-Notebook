// https://codeforces.com/problemset/problem/710/F
#include <bits/stdc++.h>
 
#define forn(i,n) for(int i = 0; i < n; ++i)
#define sz(v) int(v.size())
#define pb push_back
#define el '\n'
 
using namespace std;
 
typedef vector<int> vi;
typedef long double ll;

vector<string> st[2]; 
const static int N = 1e5 + 11, alpha = 26;
int to[2][20][N][alpha], fail[2][20][N], end_w[2][20][N], cnt_w[2][20][N], fail_out[2][20][N];
struct aho_corasick{
  int sz=0, words=0, id, b;
  aho_corasick(){}
  aho_corasick(vi& v, int id, int b): id(id), b(b){
    int n = 10;
    for(int i: v) n += sz(st[id][i]);
    forn(i, n) fail_out[id][b][i] = end_w[id][b][i] = cnt_w[id][b][i] = fail[id][b][i] = 0;
    forn(i, n) forn(j, alpha) to[id][b][i][j] = 0;
    for(int i: v) add(st[id][i]);
    build();
  }
  inline int conv(char ch) { return  ch-'a'; }
  void add(string &s) {
    int v = 0;
    for(char c : s) {
      int x = conv(c);
      if(!to[id][b][v][x]) to[id][b][v][x] = ++sz;
      v = to[id][b][v][x];
    }
    ++cnt_w[id][b][v];
    end_w[id][b][v] = ++words;
  }
  void build() {
    queue<int> q{{0}};
    while(sz(q)) {
      int u = q.front();  q.pop();
      forn(i, alpha) {
        int v = to[id][b][u][i];
        if(!v) to[id][b][u][i] = to[id][b][ fail[id][b][u] ][i];
        else q.push(v);
        if(!u || !v) continue;
        fail[id][b][v] = to[id][b][ fail[id][b][u] ][i];
        fail_out[id][b][v] = end_w[id][b][ fail[id][b][v] ] ? fail[id][b][v] : fail_out[id][b][ fail[id][b][v] ];
        cnt_w[id][b][v] += cnt_w[id][b][ fail[id][b][v] ];
      }
    }
  }
  int match(string &s){
    if(words == 0) return 0;
    int v = 0, mat = 0;
    for(char c: s) mat += cnt_w[id][b][v = to[id][b][v][conv(c)]];
    return mat;
  }
};
 
struct bin_aho{
  vi str[20];
  int id;
  aho_corasick aho[20];
 
  bin_aho(int id): id(id){}
  void add_w(int idx){
    int i = 0;
    vi cur{idx};
    while(sz(str[i])){
      for(int k: str[i]) cur.pb(k);
      str[i].clear();
      aho[i++] = aho_corasick();
    }
    aho[i] = aho_corasick(str[i] = cur, id, i);
  }
  int match(string& p){
    int ans = 0;
    forn(i, 20) ans += aho[i].match(p);
    return ans;
  }
};
 
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  
  bin_aho a[2] = {bin_aho(0), bin_aho(1)};
  int n; cin >> n;
  forn(i, n){
    int t; cin >> t;
    string s; cin >> s;
    if(t <= 2) {
      st[t-1].pb(s);
      a[t-1].add_w(sz(st[t-1])-1);
    } else cout << a[0].match(s) - a[1].match(s) << endl;
  }
}