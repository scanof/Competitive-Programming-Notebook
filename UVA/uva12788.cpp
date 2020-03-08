#include <bits/stdc++.h>

#define forn(i,n) for(int i= 0; i<n; ++i)
#define for1(i,n) for(int i= 1; i<=n; ++i)
#define fore(i,l,r) for(int i= l; i<=r; ++i)
#define pb push_back
#define el '\n';
#define d(x) cout<< #x<< " "<< x<< el;

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
int n;
vector<int> arr;
vector<int> diff;
int ans;
int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<<fixed;
    while(cin>>n){
        arr.resize(n);
        forn(i,n){
            cin>>arr[i];
        }
        diff.pb(0);
        for1(i,n-1){
            if(arr[i]<arr[i-1]) diff.pb(i);
        }
        diff.pb(n);
        ans=0;
        if(diff.size()==2){
            ans = n;
        }
        else {forn(i, diff.size()-2){
            ans = max(ans, diff[i+2]-diff[i]);
        }
        }
        cout<<ans<<el;
        arr.clear();
        diff.clear();
    }

}
