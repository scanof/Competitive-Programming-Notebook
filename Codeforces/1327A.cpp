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

const ll inf = LONG_LONG_MAX;
const int nax = 1e5+200;
const double mpi = acos(-1);
const double eps= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
//    cout<< setprecision(20)<< fixed;
    int t;
    cin>> t;
    while(t--){
        int n;
        cin>> n;
        int k;
        cin>> k;
        if(n<k){
            cout<< "NO"<<el;
            continue;
        }
        if(n/k < k ){
            cout<< "NO"<<el;
            continue;
        }
        if(n%2==0){
            if(k%2==1){
                cout<< "NO"<<el;
            }else{
                cout<< "YES"<<el;
            }
        }else{
            if(k%2==0){
                cout<< "NO"<<el;
            }else{
                cout<< "YES"<<el;
            }
        }
    }
}
