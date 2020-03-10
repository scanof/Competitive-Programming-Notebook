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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const ll INF = LONG_LONG_MAX;
const double MAXN = 1e6;
const double PI = acos(-1);
const double EPS= 1e-10;
const ll limite = 1e16;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(20)<< fixed;
    int t, n;
    ll k;
    cin>> t;
    while(t--){
        cin>> n>> k;
        ll a[n];
        ll num= 1;
        vector<ll> pot;
        pot.pb(-1);
        while(num*k<= (limite)){
            num*= k;
            pot.pb(-num);
        }
        ll sum = 0;
        forn(i,n){
            cin>> a[i];
            sum += a[i];
        }
        int m = pot.size();
        bool seen[m];
        memset(seen , false, sizeof seen);
        if(sum == 0){
            cout<< "YES"<<el;
            continue;
        }
        int works = 0;
        sort(pot.begin(), pot.end());
        forn(j,n){
            if(works==-1) break;
            num = a[j];
            if(num==0) continue;
            int i = lower_bound(pot.begin(),pot.end(),-num)- pot.begin();
            if(lower_bound(pot.begin(),pot.end(),-num) == pot.end()){
                works = -1;
                break;
            }
            while(num && i<m){
                if(num< -pot[i]){
                    ++i;
                    continue;
                }
                if(seen[i]){
                    works= -1;
                    break;
                }
                num-= -pot[i];
                seen[i]= true;
                ++i;
            }
            if(num!=0){
                works = -1;
                break;
            }
        }
        if(works == -1) cout<< "NO"<< el;
        else cout<< "YES"<<el;
    }
}
