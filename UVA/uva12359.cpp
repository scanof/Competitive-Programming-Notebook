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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

const ll INF = LONG_LONG_MAX;
const double PI = atan(1)*4;
const int MAXN = 1<<21;
const double EPS= 1e-10;

struct node{
    int next[26]; //hijos
//    char c; // que letra esta en este nodo
    bool terminal=false; // indica si esta es la ultima letra de una palabra
    node(){
        forn(i,26) next[i]=0;
    }
//    node(char _x) : c(_x) {}
};

int sz;
node words[2][MAXN];

void extend(const string s, int w ,int &sz){
    int n= s.size();    int v= 0;
    forn(i,n){
        int idx= s[i]-'a';
        if(words[w][v].next[idx])  v= words[w][v].next[idx];
        else{
            words[w][v].next[idx]= sz;
            v=sz;
            words[w][sz++]= node();
        }
        if(i==n-1) words[w][v].terminal= true;
    }
}

int cnt[2][26];

ll calc(int w, int u){
    ll res= 1;
    forn(i,26){
        if(words[w][u].next[i]){
            res+= calc(w, words[w][u].next[i]);
            if(u) cnt[w][i]++;
        }
    }
    return res;
}
int sp, ss;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int szp, szs;
    string s,p;
    while(cin>> szp >> szs){
        if(szp+szs == 0) return 0;
        memset(cnt, 0, sizeof cnt);
        forn(i,sp) words[0][i] = node();
        forn(i,ss) words[1][i] = node();
        sp= 1;
        ss= 1;
        forn(i,szp){
            cin>> p;
            extend(p,0,sp);
        }
        forn(i,szs){
            cin>> s;
            reverse(s.begin(),s.end());
            extend(s,1,ss);
        }
        ll ans= 0;
        ans+= 1LL*(calc(0,0)-1)*(calc(1,0)-1);
        forn(i,26){
            ans-= cnt[0][i] * cnt[1][i];
        }
        cout<<ans<<el;
    }
}
