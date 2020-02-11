#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)
#define PI atan(1)*4

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

int n;
int arr[1005];
int lefta[1005], righta[1005];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    forn(i,n){
        lefta[i]=1;
        righta[i]=1;
    }
    forn(i,n){
        cin>> arr[i];
    }

    for1(i,n-1){
        if(arr[i-1]<=arr[i]) lefta[i]= lefta[i-1]+1;
    }
    for(int i= n-1 ; i>0 ; --i){
        if(arr[i]<= arr[i-1]) righta[i-1] = righta[i]+1;
    }
    int maxi= 0;
    forn(i,n){
        arr[i]= lefta[i]+righta[i]-1;
        maxi= max(arr[i],maxi);
    }
    cout<< maxi<<el;
}
