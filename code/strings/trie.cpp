const static int N = 2e6, alpha = 26, B = 30; // MAX: abecedario, bits
int to[N][alpha], cnt[N], sz;
inline int conv(char ch){ return ch - 'a'; }  //  CAMBIAR
string to_bin(int num, int bits){  // B: Max(bits),  bits: size 
  return bitset<B>(num).to_string().substr(B - bits);}
// AGREGAR LO QUE HAYA QUE RESETEAR !!!!
void init(){ 
  forn(i, sz+1) cnt[i] = 0, memset(to[i], 0, sizeof to[i]);
  sz = 0;
}
void add(const string &s){
  int u = 0;
  for(char ch: s){
    int c = conv(ch);
    if(!to[u][c]) to[u][c] = ++sz;
    u = to[u][c];
  }
  cnt[u]++;
}