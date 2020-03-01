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
    string s;
    cin>> s;
    int num= 0;
    int fi = n;
    forn(j,fi+20){
        char ch= 'a';
        int pos = -1;
        forn(i,n){
            if(ch<s[i]){
                if(i+1<n && s[i]-s[i+1]==1){
                    ch= s[i];
                    pos = i;
                }
                if(i-1>=0 && s[i]-s[i-1]==1){
                    ch = s[i];
                    pos = i;
                }
            }
        }
        int i = pos;
        if(pos!=-1){
            if(i+1<n && s[i]-s[i+1]==1){
                s[i] = '*';
                ++num;
            }
            if(i-1>=0 && s[i]-s[i-1]==1){
                s[i] = '*';
                ++num;
            }
        }else{
            break;
        }
        string tmp = "";
        forn(i,n){
            if(s[i]!='*'){
                tmp += s[i];
            }
        }
        s= tmp;
        n= s.size();
    }
    cout<< num<<el;
}
