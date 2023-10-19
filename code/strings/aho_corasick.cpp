const static int N = 1e5+1, alpha = 26;
int sz, to[N][alpha], fail[N], end_w[N], cnt_w[N], fail_out[N];
inline int conv(char ch) { return  ch-'a'; }
struct aho_corasick{
  int words=0;
  aho_corasick(vector<string>& str){ 
    forn(i, sz+1) fail[i] = end_w[i] = cnt_w[i] = fail_out[i] = 0;
    forn(i, sz+1) memset(to[i], 0, sizeof to[i]);
    sz = 0;
    for(string& s: str) add(s); 
    build(); 
  }
  void add(string &s) {
    int v = 0;
    for(char ch : s) {
      int c = conv(ch);
      if(!to[v][c]) to[v][c] = ++sz;
      v = to[v][c];
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
    for(char ch: s) {
      v = to[v][conv(ch)];
      mat += cnt_w[v];
    }
    return mat;
  }
};