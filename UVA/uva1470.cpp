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

const int MAXN = 4e5+20;

string s;
int d2[MAXN];
void manacher(){
    int l=0, r=-1, n=s.size();
    forn(i, n){
        int k=(i>r? 0 : min(d2[l+r-i+1], r-i+1))+1;
        while(i+k-1<n && i-k>=0 && s[i+k-1]==s[i-k]) k++;
        d2[i] = --k;
        if(i+k-1 > r) l=i-k, r=i+k-1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>>n;
    forn(k,n){
        cin>>s;
        memset(d2, 0,sizeof d2);
        manacher();
        int ans=0;

        forn(i,s.size()+1){
            d2[i]*=2;
        }
        for(int i= 0; i<s.size(); ++i){
            if(d2[i]==0) continue;

            for(int l = (d2[i])/4*4 ; l>ans ; l-=4){
				if (d2[i-l/4]>=l/2 && d2[i+l/4]>=l/2)
					ans=max(ans,l);
			}
        }
        cout<<ans<<el;
    }
}
