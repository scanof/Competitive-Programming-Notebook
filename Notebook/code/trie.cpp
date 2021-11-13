const static int N = 1<<21;
const static int alpha = 26;
int trie[N][alpha], cnt[N], sz;
void init(){ memset(trie[0], 0 ,sizeof trie[0]); sz = 0; }
void add(const string &s){
  int v= 0;
  for(char ch: s){
    int c = ch-'a';
    int &next = trie[v][c];
    if(!next){
      next = ++sz;
      memset(trie[next], 0, sizeof trie[next]);
    }
    v= next;
  }
  cnt[v]++;
}
