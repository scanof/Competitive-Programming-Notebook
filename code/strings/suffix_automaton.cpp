struct node {
  int len, link;
  map<char, int> to;  // if TLE --> change to array<int, 27> to; 
  bool terminal;
};

const int N = 4e5+1; // el doble del MAXN
node st[N];
int sz, last, occ[N], cnt[N];
bool seen[N];

struct suf_aut{
  suf_aut(string& s){ 
    forn(i, sz) st[i] = node();
    sz = 1;
    st[0].len = st[0].terminal = last = 0;
    st[0].link = -1;
    for(char c: s) extend(c);
  }
  void extend(char c) {
    int v = sz++, p = last;
    st[v].len = st[p].len + 1;
    while(p != -1 && !st[p].to[c]) st[p].to[c] = v, p = st[p].link;
    if(p == -1) st[v].link = 0;
    else{
      int q = st[p].to[c];
      if(st[p].len + 1 == st[q].len) st[v].link = q;
      else{
        int w = sz++;
        st[w].len = st[p].len + 1;
        st[w].to = st[q].to;
        st[w].link = st[q].link;
        while(p != -1 && st[p].to[c] == q) st[p].to[c] = w, p = st[p].link;
        st[q].link = st[v].link = w;
      }
    }
    cnt[last = v] = 1;
  }
  int dfs_occ(int v){
    if(occ[v]) return occ[v];
    occ[v] = st[v].terminal;
    for(auto &[_, u] : st[v].to) occ[v] += dfs_occ(u);
    return occ[v];
  }
  void calc_cnt(){
    vi ord(sz - 1);  iota(all(ord), 1);
    sort(all(ord), [&](int i, int j){ return st[i].len > st[j].len; });
    for(int v: ord) cnt[st[v].link] += cnt[v];  // Add cnt to link
  }
  string LCS(string &t){
    int v = 0, l = 0;
    ii mx{0, -1};
    forn(i, sz(t)){
      while(v && !st[v].to.count(t[i])) v = st[v].link, l = st[v].len;
      if(st[v].to.count(t[i])) v = st[v].to[t[i]], ++l;
      mx = max(mx, {l, i}); // LCS ending at position i
    }
    return t.substr(mx.se - mx.fi + 1, mx.fi);
  }
  int cyclic_match(string& t){
    int n = sz(t), v = 0, l = 0, ans = 0;
    t += t;
    forn(i, sz(t)){
      while(v && !st[v].to.count(t[i])) v = st[v].link, l = st[v].len;
      if(st[v].to.count(t[i])) v = st[v].to[t[i]], ++l;
      if(i >= n){
        if(v && st[st[v].link].len >= n) v = st[v].link, l = st[v].len;
        if(!seen[v] && l >= n) seen[v] = 1, ans += cnt[v]; // Match
      }
    }
    return ans;
  }
};