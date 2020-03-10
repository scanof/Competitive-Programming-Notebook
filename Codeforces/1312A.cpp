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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(20)<< fixed;
    int t, n , m;
    cin>> t;
    while(t--){
        cin>> n>> m;
        if(n%m==0){
            cout<< "YES"<<el;
        }else{
            cout<< "NO"<<el;
        }

    }
}
