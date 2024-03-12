// https://algo.sk/br24/problem.php?problem=d2-avgavg
#include <bits/stdc++.h>

#define forn(i,n) for(int i=0; i < n; ++i)
#define for1(i,n) for(int i=1; i <= n; ++i)
#define fore(i,l,r) for(int i=l; i <= r; ++i)
#define el '\n'
#define sz(v) int(v.size())
#define all(v) v.begin(),v.end()
#define d(x) cout <<#x << " : " << x << el;

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

struct frac{
  ll num, den;
  frac(){}
  frac(ll num, ll den):num(num), den(den){ 
    if(!num) den = 1;
    if(num > 0 && den < 0) num = -num,  den = -den;
    simplify(); 
  }
  void simplify(){
    ll g = __gcd(abs(num), abs(den));
    if(g) num /= g,  den /= g;
  }
  frac operator+(const frac& b){ return {num*b.den + b.num*den, den*b.den};}
  frac operator-(const frac& b){ return {num*b.den - b.num*den, den*b.den};}
  frac operator*(const frac& b){ return {num*b.num, den*b.den};}
  bool operator<(const frac& b)const{ return num*b.den < den*b.num; }
};

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n, k, a[34], sum;
  bool dp[34][34][34][101][101];
  cin >>n >> k;
  forn(i, n) cin >> a[i], sum += a[i];

  queue<array<int, 5>> q;
  auto go = [&](int i, int s1, int s2, int sum1, int sum2){
    if(!dp[i][s1][s2][sum1][sum2]) q.push({i, s1, s2, sum1, sum2});
    dp[i][s1][s2][sum1][sum2] = 1;
  };
  pair<double, frac> best = {1e9, frac{1, 1}};
  frac me = frac(k, 1);
  // Caso base
  go(0, 0, 0, 0, 0);
  while(sz(q)){
    auto [i, s1, s2, sum1, sum2] = q.front(); q.pop();
    // Condicion de parada
    if(i == n){
      int s3 = n - s1 - s2;
      if(!s1 || !s2 || ! s3) continue;
      int sum3 = sum - sum1 - sum2;
      frac a = frac{sum1, s1}, b = frac{sum2, s2}, c = frac{sum3, s3};
      frac avg = (a + b + c) * frac{1, 3};
      frac dif = avg - me;
      double cur = abs(1.0*dif.num / dif.den);
      best = min(best, {cur, avg});
      continue;
    }
    // Transiciones
    go(i+1, s1+1, s2, sum1 + a[i], sum2);
    go(i+1, s1, s2+1, sum1, sum2 + a[i]);
    go(i+1, s1, s2, sum1, sum2);
  }
  auto [_, avg] = best;
  cout << avg.num << "/" << avg.den << el;
}
