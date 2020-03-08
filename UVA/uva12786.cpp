#include <bits/stdc++.h>

#define forn(i,n) for(int i= 0; i<n; ++i)
#define for1(i,n) for(int i= 1; i<=n; ++i)
#define fore(i,l,r) for(int i= l; i<=r; ++i)
#define fored(i,r,l) for(int i= r; i>=l; --i)
#define pb push_back
#define el '\n';
#define d(x) cout<< #x<< " "<< x<< el;

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
int n;
int sum;
bool imposible;
int main(){
//    ios_base:: sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<<fixed;
    while(cin>>n){
        int arr[n];
        sum=0;
        imposible = false;
        forn(i,n){
            cin>>arr[i];
            sum+=arr[i];
        }
        if(sum%2==1) imposible = true;
        sort(arr, arr+n);

        fored(i, n-1, 0){
            if(imposible) break;
            int res = arr[i];
            if(res==0) continue;
            if(res>i) imposible = true;
            int p = i-1;
            while(res>0){
                int grupo =0;
                while(p>0 && arr[p]==arr[p-1]){
                    p--;
                    grupo++;
                }
                grupo++;
                for(int j = p; j<p+min(grupo, res); j++){
                    arr[j]--;
                    if(arr[j]<0){
                        imposible = true;
                        break;
                    }
                }
                res-=grupo;
                p--;
                arr[i]=0;
            }
            if(imposible) break;
        }
        if(imposible) {
                cout<<0<<el;
        }else {
            forn(i,n){
                if(arr[i]!=0) imposible = true;
            }
            if(imposible) {
                cout<<0<<el;
            }else cout<<1<<el;
        }
    }

}
