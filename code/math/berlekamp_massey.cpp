// taken from https://codeforces.com/blog/entry/61306
struct ber_ma{
	vi BM(vi &x){
		vi ls,cur; int lf,ld;
		forn(i,sz(x)){
			ll t=0;
			forn(j,sz(cur)) t=(t+x[i-j-1]*(ll)cur[j])%mod;
			if((t-x[i])%mod==0) continue; 
			if(!sz(cur)){
				cur.resize(i+1);
				lf=i; ld=(t-x[i])%mod;
				continue;
			}
			ll k=-(x[i]-t)*inv(ld,mod);
			vi c(i-lf-1); c.pb(k);
			forn(j,sz(ls)) c.pb(-ls[j]*k%mod);
			if(sz(c)<sz(cur)) c.resize(sz(cur));
			forn(j,sz(cur)) c[j]=(c[j]+cur[j])%mod;
			if(i-lf+sz(ls)>=sz(cur)) ls=cur,lf=i,ld=(t-x[i])%mod;
			cur=c;
		}
		forn(i,sz(cur)) cur[i]=(cur[i]%mod+mod)%mod;
		return cur;
	}
	
	int m; //length of recurrence
	//a: first terms
	//h: relation
	vector<ll> a, h, t_, s, t;
	//calculate p*q mod f
	inline vector<ll> mull(vector<ll> p, vector<ll> q){
		forn(i,2*m) t_[i]=0;
		forn(i,m) if(p[i])
			forn(j,m)
				t_[i+j]=(t_[i+j]+p[i]*q[j])%mod;
		for(int i=2*m-1;i>=m;--i) if(t_[i])
			forn(j,m)
				t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%mod;
		forn(i,m) p[i]=t_[i];
		return p;
	}
	inline ll calc(ll k){
    if(k < sz(a)) return a[k];
		forn(i,m) s[i]=t[i]=0;
		s[0]=1; 
		if(m!=1) t[1]=1; 
		else t[0]=h[0];
		
		while(k){
			if(k&1LL) s = mull(s,t);
			t = mull(t,t); k/=2;
		}
		ll su=0;
		forn(i,m) su=(su+s[i]*a[i])%mod;
		return (su%mod+mod)%mod;
	}
	ber_ma(vi &x){
		vi v = BM(x); m=sz(v);
		h.resize(m), a.resize(m), s.resize(m);
		t.resize(m), t_.resize(2*m);
		forn(i,m) h[i]=v[i],a[i]=x[i];
	}	
};