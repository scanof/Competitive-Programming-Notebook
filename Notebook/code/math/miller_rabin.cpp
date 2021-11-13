ll mulmod(ll a, ll b, ll m) {
	ll r=a*b-(ll)((long double)a*b/m+.5)*m;
	return r<0?r+m:r;
}
ll binpow(ll b, ll e, ll m){
  ll r = 1;
  while(e){
    if(e&1) r = mulmod(r, b,m);
    b = mulmod(b,b,m);
    e = e/2;
  }
  return r;
}

bool is_prime(ll n, int a, ll s, ll d){
	if(n==a) return true;
	ll x=binpow(a,d,n);
	if(x==1 || x+1==n)return true;
	forn(k,s-1){
		x=mulmod(x,x,n);
		if(x==1) return false;
		if(x+1==n) return true;
	}
	return false;
}
int ar[]={2,3,5,7,11,13,17,19,23,29,31,37};
bool rabin(ll n){ // true iff n is prime
	if(n==2) return true;
	if(n<2 || n%2==0) return false;
	ll s=0,d=n-1;
	while(d%2==0)++s,d/=2;
	forn(i,12) if(!is_prime(n,ar[i],s,d)) return false;
  return true;
}

///////////////////////////////////////

bool isPrime(ll n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	ll s=0,d=n-1;
	while(d%2==0)++s,d/=2;
	for (ll a : A) {   // ^ count trailing zeroes
		ll p = binpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = mulmod(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}
