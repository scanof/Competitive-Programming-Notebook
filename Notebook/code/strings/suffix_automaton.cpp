struct node {
  int len, link;
  map<char, int> to;
  bool terminal;
};

const int nax = 1<<21;
node st[nax];
int sz, last;
int occ[nax];

void sa_init() { ///// HACELEE INIT!!!
  forn(i,sz) st[i] = node();
  st[0].len = last = st[0].terminal = 0;
  st[0].link = -1;
  sz=1;
}

void sa_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].to.count(c)) {
    st[p].to[c] = cur;
    p = st[p].link;
  }
  if (p == -1)  st[cur].link = 0;
  else {
    int q = st[p].to[c];
    if (st[p].len + 1 == st[q].len) st[cur].link = q;
    else {
      int w = sz++;
      st[w].len = st[p].len + 1;
      st[w].to = st[q].to;
      st[w].link = st[q].link;
      while (p != -1 && st[p].to[c] == q) {
        st[p].to[c] = w;
        p = st[p].link;
      }
      st[q].link = st[cur].link = w;
    }
  }
  last = cur;
}

void dfs(int v){
  if(occ[v] != 0) return;
  occ[v] = st[v].terminal;
  for(auto &e : st[v].to){
    dfs(e.se);
    occ[v] += occ[e.se];
  }
}

string lcs(string &S, string &T){
  sa_init();
  for (char c : S) sa_extend(c);

  int v = 0, l = 0, best = 0, bestpos = 0;
  forn(i, sz(T)){
    while (v && !st[v].to.count(T[i])) {
      v = st[v].link , l = st[v].len ;
    }
    if (st[v].to.count(T[i])) {
      v = st[v].to[T[i]];
      l++;
    }
    if (l > best) {
      best = l;
      bestpos = i;
    }
  }
  // best guarda el tamano del longest common substring
  return T.substr(bestpos - best + 1, best);
}