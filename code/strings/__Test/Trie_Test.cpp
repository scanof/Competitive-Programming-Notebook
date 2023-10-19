// https://codeforces.com/gym/104011/problem/C
#include <bits/stdc++.h>

#define el '\n'
#define forn(i,n) for(int i=0; i<n; ++i)
#define pb push_back
#define all(v) v.begin(),v.end()
#define sz(v) int(v.size())
#define fi first
#define se second
#define d(x) cout << #x << " = " << x << el

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int inf = 1e9 + 10;

const static int N = 2e6, alpha = 26, B = 30; // MAX: abecedario, bits
int to[N][alpha], cnt[N], sz, n, k;
inline int conv(char ch){ return ch - 'a'; }  //  CAMBIAR
string to_bin(int num, int bits){  // B: Max(bits),  bits: size 
  return bitset<B>(num).to_string().substr(B - bits);}
// AGREGAR LO QUE HAYA QUE RESETEAR !!!!
void init(){ 
  forn(i, sz+1) cnt[i] = 0, memset(to[i], 0, sizeof to[i]);
  sz = 0;
}
void add(const string &s){
  int v = 0;
  for(char ch: s){
    int c = conv(ch);
    if(!to[v][c]) to[v][c] = ++sz;
    v = to[v][c];
  }
  cnt[v]++;
}

int ans = 0;
int dfs(int v){
  if(*max_element(to[v], to[v]+alpha) == 0) return 1; // hoja

  int sum = cnt[v];
  vi val;
  for(int u : to[v]){
    if(!u) continue;
    val.pb(dfs(u));
    sum += val.back();
  }

  sort(all(val), greater<>());
  int idx = 0;
  while(sum > k){
    ++ans;
    sum -= val[idx++];
  }
  return sum;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin >> n >> k;
  cin.tie(0); cout.tie(0);
  forn(i, n) {
    string s; cin >> s;
    add(s);
  }
  cout << ans + (dfs(0) + k-1)/k << el;
}