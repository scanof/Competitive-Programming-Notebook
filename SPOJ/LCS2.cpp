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

struct state {
    int len, link;
    int next[26];
    state(){
        for(int i=0; i< 26; ++i){
            next[i]=-2;
        }
    }
    int cnt = 1; // ocurrencias forma 2
};

inline int convert(char ch) { // Function for properly index characters
    return ((ch >= 'a' && ch <= 'z') ? ch-'a' : ch-'0'+26);
}
const int MAXN = 5e5+20;
state st[MAXN];
int sz, last;

void sa_init() {
    forn(i,MAXN){
        st[i]= state();
    }
    st[0].len = 0;
    st[0].link = -1;
    st[0].cnt= 0;
    ++sz;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    int ch = convert(c);
    while (p != -1 && st[p].next[ch]==-2) {
        st[p].next[ch] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[ch];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            forn(i,26){
                st[clone].next[i] = st[q].next[i];
            }
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[ch] == q) {
                st[p].next[ch] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
            st[clone].cnt=0;
        }
    }
    last = cur;
}

int allmask;

int goods[MAXN];
int lens[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s;
    cin>> s;
    sa_init();
    int n= s.size();
    forn(i,n) sa_extend(s[i]);
    forn(i,sz){
        lens[i]=INT_MAX;
    }
    vector<string> pat;
    pat.reserve(11);
    string t;
    while(cin>>t){
        pat.pb(t);
    }
    n= pat.size();
    allmask= (1<<n)-1;
    int v=0;
    int best=0, l=0;
    int lentmp[sz];
    forn(i,sz){
        lentmp[i]=0;
    }
    int sufi[sz];
    forn(i,sz) sufi[i]= -1;
    forn(i,sz){
        sufi[st[i].link]=i;
    }
    vector<int> cual;
    cual.reserve(MAXN);
    forn(i,n){
        v=best=l=0;
        for(char c: pat[i]){
            int ch = convert(c);
            int lon= l;
            while (v && st[v].next[ch]==-2) {
                goods[v]|= (1<<i);
                lentmp[v]= max(lentmp[v],min(lon,st[v].len));
                lon = min(lon,st[v].len);
                v = st[v].link ;
                l = st[v].len ;
            }
            if (st[v].next[ch]!=-2){
                v = st[v].next[ch];
                int p=v;
                l++;
                goods[v]|= (1<<i);
                if(goods[v]==allmask) cual.pb(v);
                lentmp[v]= max(lentmp[v],l);
            }
            if (l > best) {
                best = l;
            }
        }
        forn(i,sz){
            lens[i]= min(lens[i], lentmp[i]);
            lentmp[i]=0;
        }
    }
    best=0;

    for(int i: cual){
        if(i==0) continue;
        best= max(best,lens[i]);
    }
    cout<<best<<el;
}
