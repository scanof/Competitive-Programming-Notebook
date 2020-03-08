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

const int MAXN = 7e6+ 20;
const int MAXC = 26;
int sz;
string t;
int p;
string pat[MAXN];
vi cnt[MAXN];

inline int conv(char ch){
    return ch-'a';
}

struct state{
    int link ;
    vi out;
    int next[MAXC];
    state(){
        link = -1;
        memset(next, -1, sizeof next);
    }
};

state st[MAXN];

void build(){
    forn(i,sz) st[i] = state();
    st[0].link= 0; sz= 1;
    forn(i,p){
        const string &word = pat[i];
        int cur = 0;
        forn(j,word.size()){
            int ch = conv(word[j]);
            if(st[cur].next[ch]==-1){
                st[cur].next[ch] = sz++;
            }
            cur = st[cur].next[ch];
        }
        st[cur].out.pb(i);
    }
    queue<int> q;
    forn(ch,MAXC){
        if(st[0].next[ch]==-1)
            st[0].next[ch] = 0;
        else{
            st[st[0].next[ch]].link = 0;
            q.push(st[0].next[ch]);
        }
    }
    while(!q.empty()){
        int state = q.front();
        q.pop();
        forn(ch,MAXC){
            if(st[state].next[ch]!=-1){
                int fail = st[state].link;
                while(st[fail].next[ch]==-1)
                    fail = st[fail].link;
                fail = st[fail].next[ch];
                int next = st[state].next[ch];
                st[next].link = fail;
                for(int a : st[fail].out) st[next].out.pb(a);
                q.push(next);
            }
        }
    }
}

int findNext(int cur, char c){
    int ans = cur;
    int ch = conv(c);
    while(st[ans].next[ch]==-1)
        ans = st[ans].link;
    return st[ans].next[ch];
}

void searchWords(){
    build();
    int cur = 0, tmp= 0;
    forn(i, t.size()){
        cur = findNext(cur, t[i]);
        for(int x: st[cur].out)
            cnt[x].pb(i);
    }
    int ant = -2;
    bool work = true;
    forn(i,p){
        work = false;
        int m = pat[i].size();
        for(int j: cnt[i]){

            if(ant<= (j- m)){
                ant = j;
                work = true;
                break;
            }
        }
        if(!work){
            cout << "no"<< el;
            return ;
        }
    }
    cout << "yes"<<el;
}

int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<<fixed;
    int q;
    while(cin>> q){
        cin>>t;
        while(q--){
            p=0;
            string s;
            cin>> s;

            int n= s.size();
            int i, k;
            for(i= 0, k = 0; i< n; ++i){
                if(s[i]=='*'){
                    string sb = s.substr(k,min(i-k,n-k ));
                    if(sb!=""){
                        pat[p++]= sb;
                    }
                    k= i+1;
                }
            }
            if(k!=n){
                string sb = s.substr(k,min(i-k,n-k));
                if(sb!=""){
                    pat[p++]= sb;
                }
            }
            searchWords();
            forn(i,p) cnt[i].clear();
        }
    }
}
