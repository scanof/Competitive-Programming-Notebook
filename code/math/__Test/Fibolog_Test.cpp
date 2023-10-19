#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

#define forn(i, n) for (int i = 0; i < n; ++i)
#define for1(i, n) for (int i = 1; i <= n; ++i)
#define fore(i, l, r) for (int i = l; i <= r; ++i)
#define el '\n'
#define d(x) cout << #x << " : " << x << el;
#define all(v) v.begin(), v.end()

typedef vector<int> vi;
typedef long long ll;
typedef pair<ll, ll> pll;

pll fib_log(ll n, ll mod){
  if (n == 0) return {0, 1};
  auto [a, b] = fib_log(n >> 1, mod);
  ll c = a * (2*b - a + mod) % mod;
  ll d = ((a*a % mod) + (b*b % mod)) % mod;
  if (n & 1) return {d, (c + d) % mod};
  else return {c, d};
}

vi div(ll n) {
  vi res;
  for1(i, sqrt(n)) {
    if (n % i == 0) {
      res.push_back(i);
      if (n / i != i) res.push_back(n / i);
    }
  }
  sort(all(res));
  return res;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  ll n; cin >> n;
  if(n == 5){
    cout << 20 << el;  return 0;
  }
  if(n == 2) {
    cout << 3 << el;  return 0;
  }
  if(n % 5 == 1 || n % 5 == 4) {
    vi d = div(n - 1);
    for(int x : d) {
      pll f = fib_log(x, n);
      if (f.fi == 0 && f.se == 1) {
        cout << x << el;  return 0;
      }
    }
  } else {
    vi d = div(2 * n + 2);
    for(int x : d) {
      pll f = fib_log(x, n);
      if(f.fi == 0 && f.se == 1) {
        cout << x << el;  return 0;
      }
    }
  }
}
