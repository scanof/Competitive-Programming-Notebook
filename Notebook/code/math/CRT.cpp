/*
OVERFLOW!!!

p = p1*p2*...*pk, pi pairwise coprime

a = a1 mod p1
a = a2 mod p2
..
a = ak mod pk


This function returns
a = x1 + x2*p1 + x3*p1*p2 + ... + xk*p1*p2*...*pk-1

O(k^2)
*/

ll CRT(vector<ll> &a, vector<ll> &p){
  vector<ll> x(sz(p));
  ll ans = 0, prod = 1;
  forn(i, sz(p)){
    x[i] = a[i];
    forn(j,i){
      x[i] = 1LL*(x[i] - x[j])*binpow(p[j], p[i] - 2, p[i])%p[i];
      x[i] = (x[i] + p[i])%p[i];
    }
    ans+= 1LL*x[i]*prod;
    prod *= p[i];
  }
  return ans;
}
