/// 1000234999, 1000567999, 1000111997, 1000777121, 999727999, 1070777777
const int MODS[] = { 1001864327, 1001265673 };
const ii BASE(257, 367), ZERO(0, 0), ONE(1, 1);
inline int add(int a, int b, const int& mod) { return a+b >= mod ? a+b-mod : a+b; }
inline int sbt(int a, int b, const int& mod) { return a-b < 0 ? a-b+mod : a-b; }
inline int mul(int a, int b, const int& mod) { return 1ll*a*b%mod; }
inline ll operator ! (const ii a) { return (ll(a.fi)<<32)|ll(a.se); }
inline ii operator + (const ii a, const ii b) {
  return {add(a.fi, b.fi, MODS[0]), add(a.se, b.se, MODS[1])};
}
inline ii operator - (const ii a, const ii b) {
  return {sbt(a.fi, b.fi, MODS[0]), sbt(a.se, b.se, MODS[1])};
}
inline ii operator * (const ii a, const ii b) {
  return {mul(a.fi, b.fi, MODS[0]), mul(a.se, b.se, MODS[1])};
}

const int nax = 1e5+20;
ii base[nax];
void prepare() {
  base[0] = ONE;
  for1(i,nax-1) base[i] = base[i-1]*BASE;
}
template <class type>
struct hashing {   /// HACELEEE PREPAREEEE!!!
  vector<ii> code;
  hashing(type &t) {
    code.resize(sz(t)+1);
    code[0] = ZERO;
    for1(i,sz(t))
      code[i] = code[i-1]*BASE + ii{t[i-1], t[i-1]};
  }
  ii query(int l, int r) { ///  [l,r]
    return code[r+1] - code[l]*base[r-l+1];
  }
};
