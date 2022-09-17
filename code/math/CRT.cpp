pll extendedEuclid(ll a, ll b){ // a * x + b * y = __gcd(a,b)
	ll x,y;
	if (b==0) return {1,0};
	auto p=extendedEuclid(b,a%b);
	x=p.se;
	y=p.fi-(a/b)*x;
	if(a*x+b*y==-__gcd(a,b)) x=-x, y=-y;
	return {x,y};
}
pair<pll,pll> diophantine(ll a, ll b, ll r) {
  //a*x+b*y=r where r is multiple of __gcd(a,b);
	ll d=__gcd(a,b);
  a/=d; b/=d; r/=d;
	auto p = extendedEuclid(a,b);
	p.fi*=r; p.se*=r;
	// assert(a*p.fi+b*p.se==r);
	return {p,{-b,a}}; // solutions: p+t*ans.se
}
ll inv(ll a, ll m) {
	assert(__gcd(a,m)==1);
	ll x = diophantine(a,m,1).fi.fi;
	return ((x%m)+m)%m;
}
#define MOD(a,m) (((a)%m+m)%m)
pll sol(tuple<ll,ll,ll> c){ //requires inv, diophantine
  ll a=get<0>(c), x1=get<1>(c), m=get<2>(c), d=__gcd(a,m);
  if(d==1) return pll(MOD(x1*inv(a,m),m), m);
  else return x1%d ? pll({-1LL,-1LL}) : sol(make_tuple(a/d,x1/d,m/d));
}
pair<ll,ll> crt(vector< tuple<ll,ll,ll> > &cond) { // returns: (sol, lcm)
	ll x1=0,m1=1,x2,m2;
	for(auto &t: cond){
		tie(x2,m2)=sol(t);
		if((x1-x2)%__gcd(m1,m2))return {-1,-1};
		if(m1==m2)continue;
		ll k=diophantine(m2,-m1,x1-x2).fi.se,l=m1*(m2/__gcd(m1,m2));
		x1=MOD((__int128_t)m1*k+x1,l); m1=l;
	}
	return sol(make_tuple(1,x1,m1));
} //cond[i]={ai,bi,mi} ai*xi=bi (mi); assumes lcm fits in ll