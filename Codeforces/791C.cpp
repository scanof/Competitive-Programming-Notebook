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
const int MAXN = 2e5+200;

string name(int v){
    string s ="";
    if(v<26){
        s+= ('A'+v);
        return s;
    }else{
        s+= ('A'+ v - 26);
        v-=26;
        s+= ('a'+v);
        return s;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n, len;
    cin>> n>> len;
    string s;
    bool arr[n-len+1];
    int v= 0;
    forn(i,n-len+1){
        cin>> s;
        if(s=="YES") arr[i]= true;
        else arr[i]= false;
    }
    string strs[n];
    int pos = 0;
    bool d= false;
    if(arr[0]){
        forn(i,len){
            strs[pos++]= name(v++);
        }
        d = true;
    }else{
        strs[pos++] = name(v++);
        strs[pos++] = strs[pos-1];
    }
    for(int i= 1; i<=n-len && pos<n; ++i){
        if(d){
            if(arr[i]){
                strs[pos++]= name(v++);
            }else{
                strs[pos++]= strs[pos-len+1];
            }
        }else{
            if(arr[i]){
                d= true;
                for(int j= 0; j<len-1 && pos<n; ++j){
                    strs[pos++] = name(v++);
                }
            }else{
                strs[pos++]= strs[pos-1];
            }
        }
    }
    while(pos<n){
        strs[pos++] = name(v++);
    }
    forn(i,n){
        cout<< strs[i]<< " ";
    }
    cout<<el;

}

