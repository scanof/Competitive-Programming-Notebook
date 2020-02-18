#include <bits/stdc++.h>
#define forn(i,n) for(int i=0; i<n ; ++i)
#define for1(i,n) for(int i=1; i<=n ; ++i)
#define fi first
#define se second
#define pb push_back
#define ford(i,n) for(int i=n; i>=0 ; --i)
#define fore(i,l,r) for(int i=l; i<=r ; ++i)
#define el '\n'
#define pp(x) cout << #x << ": " << "{" << x.first << " , " << x.second << "}" << el
#define MAX 1<<30

using namespace std;

typedef pair<int,int> ii;

int main(){
    string str;
    cin>> str;
    int n=str.size();
    int z[n]={0};
    int l=0,r=0;
    int seen[n]={0};
    for1(i,n-1){
        if(i<=r){
            z[i] = min(r-i+1, z[i-l]);
        }
        while(i+ z[i]<n && str[z[i]]==str[i+z[i]]) ++z[i];
        if(i+z[i]-1>r){
            l= i;
            r= i + z[i]-1;
        }
    }

    unordered_map<int,int> m;
    forn(i,n){
        ++m[z[i]];
    }
    for(int i= n-1; i>= 0; --i){
        m[i]= m[i]+ m[i+1];
    }


    forn(i,n){
        if(z[i]+i==n){
            seen[i]=1;
        }
    }
    vector<ii> pos;
    pos.reserve(n);
    forn(i,n-1){
        if(m[i]>0 && seen[n-i-1]){
            pos.pb(ii(i+1,m[i+1]+1));
        }
    }
    sort(pos.begin(),pos.end());
    cout<<pos.size()+1<<endl;
    forn(i,pos.size()){
        cout<< pos[i].fi<< " "<< pos[i].se<<endl;
    }
    cout<< n<< " "<< 1<<endl;
}
