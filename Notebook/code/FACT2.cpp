#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,l,r) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define ri(n) scanf("%d",&n)
#define sz(v) ((int)v.size())
#define all(v) v.begin(),v.end()
#define allr(v) v.rbegin(),v.rend()

using namespace std;

//typedef long long ll;
typedef double ld;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
//typedef pair<ll,ll> pll;
typedef vector<int> vi;

//const ll inf = 1e18;
const int nax = 1e5+200;
const double mpi = acos(-1);
const double eps= 1e-10;
using u128 = __uint128_t;
typedef u128 ll;
typedef vector<ll> vl;

ll mulmod(ll a, ll b, ll m) {
	ll r=(a*b)%m;
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
int ar[]={2,3,5,7,11,13,17,19,23};
bool rabin(ll n){ // true iff n is prime
	if(n==2) return true;
	if(n<2 || n%2==0) return false;
	ll s=0,d=n-1;
	while(d%2==0)++s,d/=2;
	forn(i,9) if(!is_prime(n,ar[i],s,d)) return false;
  return true;
}

ll rho(ll n){
	if(!(n&1))return 2;
	ll x=rand()%n+1; ll y=x,d=1;
	ll c=rand()%n+1;
	while(d==1){
		x=(mulmod(x,x,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		y=(mulmod(y,y,n)+c)%n;
		if(x>=y)d=__gcd(x-y,n);
		else d=__gcd(y-x,n);
	}
	return d==n?rho(n):d;
}
vl fact(ll n){ //O (lg n)^3
	if(n==1)return {};
	if(rabin(n)){return {n};}
	ll q=rho(n);
  auto l = fact(q), r = fact(n / q);
	l.insert(l.end(), all(r));
	return l;
}

ll convert(string &s){
  ll diez = 10;
  ll ans = 0;
  forn(i,sz(s)){
    ans = (ans*diez + (s[i]-'0'));
  }
  return ans;
}

void print(ll x){
  stack<int> s;
  while(x){
    s.push(x%10);
    x/=10;
  }
  while(sz(s)){
    cout<<s.top();
    s.pop();
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  cout<< setprecision(20)<< fixed;
  ll n;
  string x;
  while(cin>> x){
    n = convert(x);
    if(n==0) break;
    vl a= fact(n);
    sort(all(a));
    for(int i = 0; i<sz(a); ){
      ll prev = a[i];
      int e = 0;
      while(i<sz(a) && prev==a[i]){
        e++; i++;
      }
      print(prev);
      cout<< "^"<< e<< " ";
    }
    cout<<el;
  }
}
