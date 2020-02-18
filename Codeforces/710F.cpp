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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const int MAXN = 3e5+20;
const int p_pow = 31;
const int mod = 1e9 + 9;
int q, op, n;
char s[MAXN];
set<ll> hashes[MAXN];
ll has[MAXN];
ll p[MAXN];
int len[MAXN];

inline ll convert(char ch){
    return (ll)(ch-'a'+1);
}

int main(){
    p[0]=1;
	forn(i,MAXN) p[i]=(1LL*p[i-1]*p_pow)%mod;
    scanf("%d",&q);
    while(q--){
        scanf("%d %s",&op,&s);
        n= strlen(s);
        if(op==1){
            ll ha = 0;
            for(int i=0;i<n;i++)  ha=1ll*(1ll*ha*p_pow%mod+convert(s[i]) )%mod;
            hashes[n].insert(ha);
            ++len[n];
        }
        if(op==2){
            ll ha = 0;
            for(int i=0;i<n;i++)  ha=1ll*(1ll*ha*p_pow%mod+ convert(s[i]))%mod;
            hashes[n].erase(ha);
            --len[n];
        }
        if(op==3){
            has[0]=0;
            for(int i=0;i<n;i++) has[i+1]=1ll*(1ll*has[i]*p_pow%mod+convert(s[i]) )%mod;
			int k=1;

            ll ans = 0;
            for(int l =1;l<=n;++l){
                k=1ll*k*p_pow%mod;
                if(!len[l]) continue;
                for(int j=0; j<=n-l ;j++){
                    ll ha=1ll*(has[l+j]-1ll*has[j]*k%mod)%mod;
					ha=(ha%mod+mod)%mod;
					ans+=(hashes[l].find(ha)!=hashes[l].end());
                }
            }
            printf("%lld\n",ans); fflush(stdout);
        }
    }
}
