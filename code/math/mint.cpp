typedef long long ll;
const int mod = 1e9 + 7;
template <class T>
T bpow(T b, int e) {
  T a(1);
  do{
    if(e & 1) a *= b;
    b *= b;
  }while(e >>= 1);
  return a;
}
struct mint {
  int x;
  mint(): x(0){}
  mint(ll v) : x((v % mod + mod) % mod) {} // be careful of negative numbers!
  // Helpers to shorten code
  #define add(a, b) a + b >= mod ? a + b - mod : a + b
  #define sub(a, b) a < b ? a + mod - b : a - b
  #define yo *this
  #define cmint const mint&
  
  mint &operator += (cmint o) { return x = add(x, o.x), yo; }
  mint &operator -= (cmint o) { return x = sub(x, o.x), yo; }
  mint &operator *= (cmint o) { return x = ll(x) * o.x % mod, yo; }
  mint &operator /= (cmint o) { return yo *= bpow(o, mod-2); }

  mint operator + (cmint b) const { return mint(yo) += b; }
  mint operator - (cmint b) const { return mint(yo) -= b; }
  mint operator * (cmint b) const { return mint(yo) *= b; }
  mint operator / (cmint b) const { return mint(yo) /= b; }

  mint operator - () const { return mint() - mint(yo); }
  bool operator == (cmint b) const { return x == b.x; }
  bool operator != (cmint b) const { return x != b.x; }

  friend ostream& operator << (ostream &os, cmint p) { return os << p.x; }
  friend istream& operator >> (istream &is, mint &p) { return is >> p.x; }
};