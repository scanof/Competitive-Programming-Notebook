#include <bits/stdc++.h>
#define X get<0>
#define Y get<1>
#define Z get<2>
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(ll i=1; i<= n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define deb(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef vector<ll> vi;
typedef tuple<int,int,int> ti;
const double PI = atan(1)*4;
const int MAXN = 90;
const double EPS = 1e-9;
int dp[MAXN];
int n,x,y,z, ans;

void adjust(ti &caja){
    if(X(caja)<Y(caja)) swap(X(caja),Y(caja));
}

int main (){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(10)<< fixed;
    while(cin>>n && n!=0){
        ans=0;
        ti cajas[3*n+1];
        forn(i,n){
            cin>>x>>y>>z;
            ti caja1 = ti(x,y,z);
            adjust(caja1);
            ti caja2 = ti(z,x,y);
            adjust(caja2);
            ti caja3 = ti(y,z,x);
            adjust(caja3);
            cajas[i*3] = caja1;
            cajas[i*3+1] = caja2;
            cajas[i*3+2] = caja3;
        }
        cajas[3*n] = ti(3000, 3000, 0);
        sort(cajas, cajas+3*n+1);
        fored(i,3*n,0){
            dp[i] = Z(cajas[i]);
            fore(j,i+1,3*n){
                if(X(cajas[i])<X(cajas[j]) && Y(cajas[i])<Y(cajas[j])) dp[i] = max(dp[i], dp[j]+Z(cajas[i]));
            }
            ans = max(ans, dp[i]);
        }
        cout<<ans<<el;
        memset(dp, 0, sizeof dp);
    }
}
