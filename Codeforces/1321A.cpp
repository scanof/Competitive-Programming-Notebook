#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n;
    cin>> n;
    int a[n];
    int b[n];
    forn(i,n){
        cin>> a[i];
    }
    forn(i,n) cin>> b[i];
    int sum = 0;
    int sum2 = 0;
    forn(i,n){
        if(a[i]== b[i]) continue;
        if(b[i]){
            sum+=1; continue;
        }
        if(a[i]) sum2+=1;
    }
    if(( sum2 == sum && sum == 0) || sum2==0 ){
        cout<< -1<< el;
        return 0;
    }
    if(sum2 - sum >0 ){
        cout<< 1<<el;
        return 0;
    }else{
        int x = (1+ sum)/sum2;
        x = max(x,1);
        if(sum2* x - sum >=1){
            cout<< x<<el;
        }else{
            cout<< x+1<<el;

        }
    }
}
