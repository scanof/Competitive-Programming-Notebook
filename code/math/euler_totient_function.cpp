int phi(int n) { // O(sqrt(n))
  if(n==1) return 0;
  int ans = n;
  for (int i = 2; 1ll*i*i <= n; i++) {
    if(n % i == 0) {
      while(n % i == 0) n /= i;
      ans -= ans / i;
    }
  }
  if(n > 1) ans -= ans / n;
  return ans;
}
//////////////////
vi phi_(int n) { // O(n loglogn)
  vi phi(n + 1);
  phi[0] = 0;
  for1(i,n) phi[i] = i;
  fore(i,2,n){
    if(phi[i] != i) continue;
    for (int j = i; j <= n; j += i)
      phi[j] -= phi[j] / i;
  }
}

////////// with linear sieve when i is not a prime number
if (lp[i] == lp[i / lp[i]])
  phi[i] = phi[i / lp[i]] * lp[i];
else
  phi[i] = phi[i / lp[i]] * (lp[i] - 1);
