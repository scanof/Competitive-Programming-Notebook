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


vector<int> z_function(string s){
    int n= s.size();
    vector<int> z;  z.resize(n);
    int l=0, r=0;
    for1(i,n-1){
        if(i>r) l= r= i;
        z[i]= min(r-i,z[i-l]);
        while(i + z[i]< n && s[z[i]] ==s[z[i]+i]){
            ++z[i]; l = i;  r = i + z[i];
        }
    }
    return z;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int cases;
    cin>> cases;
    string s, p, t;
    int k;
    while(cases--){
        cin>> s>> p>> k;
        string t= p+"#"+ s;
        int szp = p.size(), szs= s.size();
        vector<int> z1 = z_function(t);
        reverse(p.begin(),p.end());
        reverse(s.begin(),s.end());
        t= p+"#"+ s;

        vector<int> z2 = z_function(t);
        vector<int> a(szs), b(szs);
        forn(i,szs){
            a[i]=z1[szp+1+i];
            b[i]=z2[szp+1+i];
        }
        reverse(b.begin(),b.end());
        ll ans=0;
        for(int i=0; i<=szs-szp; ++i){
            if(a[i]+b[i+szp-1]+k>= szp) ++ans;
        }
        cout<<ans<<el;
    }
}
