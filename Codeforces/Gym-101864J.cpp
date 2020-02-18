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

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;
const double EPS= 1e-10;


string s;
int d1[MAXN];//d1[i]=long del maximo palindromo impar con centro en i
int d2[MAXN];//d2[i]=analogo pero para longitud par

void manacher(){
    int l=0, r=-1, n=s.size();
    forn(i, n){
        int k=(i>r? 1 : min(d1[l+r-i], r-i));
        while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) ++k;
        d1[i] = k--;
        if(i+k > r) l=i-k, r=i+k;
    }
    l=0, r=-1;
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
    int q, k;
    cin>> q;

    while(q--){
        memset(d1,0,sizeof d1);
        memset(d2,0,sizeof d2);
        cin>> k;
        cin>> s;
        int n= s.size();
        vector<ll> maximo(n,n-1);
        manacher();
        forn(i,n){
            d1[i]= (d1[i]-1)*2 +1;
            d2[i]*=2;
        }
        forn(i,n){
            if(d1[i]>=k){
                ll l = k/2;
                maximo[i-l]= min(maximo[i-l], ll(i+ l -1) );
            }
            if(d2[i]>=k){
                ll l = (k+1)/2;
                maximo[i-l]= min(maximo[i-l], ll(i+l-2) );
            }
        }
//        forn(i,n) cout<< maximo[i]<< " ";
//        cout<<el;
        ll tope = n-1;
        ll ans =0;
        for(int i=n-1; i>=0; i--) {
            tope = min(tope, maximo[i]);
            maximo[i] = tope;
        }
        for(int i=0; i<n; i++) {
            ans += max(ll(0), maximo[i]-i+1);
        }
        cout<< ans<<el;
    }
}
