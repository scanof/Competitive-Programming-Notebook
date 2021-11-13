const static int N = 1<<21;
const static int alpha = 26;
int trie[N][alpha], fail[N], nodes, end_word[N], cnt_word[N], fail_out[N];
inline int conv(char ch) { // Function for properly index characters
  return ((ch >= 'a' && ch <= 'z') ? ch-'a' : ch-'A'+26);
}
void add(string &s, int i) {
  int cur = 0;
  for(char c : s) {
    int x = conv(c);
    if(!trie[cur][x]) trie[cur][x] = ++nodes;
    cur = trie[cur][x];
  }
  ++cnt_word[cur];
  end_word[cur] = i; // for i > 0
}
void build() { // HACELEEE build!!!!
  queue<int> q; q.push(0);
  while(sz(q)) {
    int u = q.front(); q.pop();
    for(int i = 0; i < alpha; ++i) {
      int v = trie[u][i];
      if(!v) trie[u][i] = trie[ fail[u] ][i]; // construir automata
      else q.push(v);
      if(!u || !v) continue;
      fail[v] = trie[ fail[u] ][i];
      fail_out[v] = end_word[ fail[v] ] ? fail[v] : fail_out[ fail[v] ];
      cnt_word[v] += cnt_word[ fail[v] ]; // obtener informacion del fail_padre
    }
  }
}
