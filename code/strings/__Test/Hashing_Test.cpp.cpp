// https://codeforces.com/problemset/problem/710/F
#include <bits/stdc++.h>

#define forn(i,n) for(int i = 0; i < n; ++i)
#define for1(i,n) for(int i = 1; i <= n; ++i)
#define sz(v) int(v.size())
#define fi first
#define se second
#define el '\n'

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;

/// 1000234999, 1000567999, 1000111997, 1000777121, 999727999, 1070777777
const int MOD[] = { 1001864327, 1001265673 }, N = 3e5;
const ii BASE(257, 367), ZERO(0, 0), ONE(1, 1);
inline int add(int a, int b, int mod) { return a+b >= mod ? a+b-mod : a+b; }
inline int sbt(int a, int b, int mod) { return a-b < 0 ? a-b+mod : a-b; }
inline int mul(int a, int b, int mod) { return ll(a) * b % mod;} 
inline ll operator ! (const ii a) { return (ll(a.fi) << 32) | a.se; }
inline ii operator + (const ii& a, const ii& b) {
  return {add(a.fi, b.fi, MOD[0]), add(a.se, b.se, MOD[1])};}
inline ii operator - (const ii& a, const ii& b) {
  return {sbt(a.fi, b.fi, MOD[0]), sbt(a.se, b.se, MOD[1])};}
inline ii operator * (const ii& a, const ii& b) {
  return {mul(a.fi, b.fi, MOD[0]), mul(a.se, b.se, MOD[1])};}

ii base[N]{ONE};
void prepare() { for1(i, N-1) base[i] = base[i-1] * BASE; }
template <class type>
struct hashing {   /// HACELEEE PREPAREEEE!!!
  vii ha;       // ha[i] = t[i]*p0 + t[i+1]*p1 + t[i+2]*p2 + ..
  hashing(type &t): ha(sz(t)+1, ZERO){
    for(int i = sz(t) - 1; i >= 0; --i) ha[i] = ha[i+1] * BASE + ii{t[i], t[i]};
  }
  ii query(int l, int r){ return ha[l] - ha[r+1] * base[r-l+1]; } //[l,r]
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  
  prepare();
  int n; cin >> n;
  map<int, unordered_set<ll>> hashes;

  forn(i, n){
    int t; cin >> t;
    string s; cin >> s;
    if(t <= 2) {
      auto ch = hashing(s).query(0, sz(s)-1);
      if(t == 1) hashes[sz(s)].insert(!ch);
      else{
        hashes[sz(s)].erase(!ch);
        if(!sz(hashes[sz(s)])) hashes.erase(sz(s));
      }
    } else{
      int ans = 0;
      for(auto& [szs, st]: hashes){
        if(szs > sz(s)) break;
        string t = s.substr(sz(s) - szs, szs);
        auto ch = hashing(t).query(0, szs-1);
        ans += st.count(!ch);
        
        int r = sz(s) - szs - 1;
        while(r >= 0){
          ch = ch - ii{s[r + szs], s[r + szs]} * base[szs - 1];
          ch = ch * BASE + ii{s[r], s[r]};
          ans += st.count(!ch);
          --r;
        }
      }
      cout << ans << endl;
    }
  }
}
