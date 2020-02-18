#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(int i=1; i<= (int)n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

struct state {
    int len, link;
    map<char, int> next;
    int cnt = 1; // ocurrencias forma 2
    int idx =-1;
};

const int MAXN = 1<<21;
state st[MAXN];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].cnt= 0;
    ++sz;
    last = 0;
}

void sa_extend(char c, int idx) {
    int cur = sz++;
    st[cur].idx = idx;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].idx = st[q].idx;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
            st[clone].cnt=0;
        }
    }
    last = cur;
}


state st2[MAXN];
int sz2, last2;

void sa_init2() {
    st2[0].len = 0;
    st2[0].link = -1;
    st2[0].cnt= 0;
    ++sz2;
    last2 = 0;
}

void sa_extend2(char c, int idx) {
    int cur = sz2++;
    st2[cur].idx = idx;
    st2[cur].len = st2[last2].len + 1;
    int p = last2;
    while (p != -1 && !st2[p].next.count(c)) {
        st2[p].next[c] = cur;
        p = st2[p].link;
    }
    if (p == -1) {
        st2[cur].link = 0;
    } else {
        int q = st2[p].next[c];
        if (st2[p].len + 1 == st2[q].len) {
            st2[cur].link = q;
        } else {
            int clone = sz2++;
            st2[clone].len = st2[p].len + 1;
            st2[clone].next = st2[q].next;
            st2[clone].link = st2[q].link;
            st2[clone].idx = st2[q].idx;
            while (p != -1 && st2[p].next[c] == q) {
                st2[p].next[c] = clone;
                p = st2[p].link;
            }
            st2[q].link = st2[cur].link = clone;
            st2[clone].cnt=0;
        }
    }
    last2 = cur;
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    string s, t;
    cin>> s;
    sa_init();
    int n= s.size();
    forn(i,n) sa_extend(s[i], i);
    // Terminal nodes
    sa_init2();
    forn(i,n) sa_extend2(s[n-i-1],n-i-1);
    int v;
    int q;
    cin>> q;
    ll ans=0;
    string tr;
    while(q--){
        cin>> t;
        tr= t;
        int m= t.size();
        if(m>n || m==1) continue;
        int lens[m+1];
        v=0;
        forn(i,m) tr[i]= t[m-i-1];
        forn(i,m+1){
            lens[i]=0;
        }
        forn(i,m){
            if(st[v].next.count(t[i])){
                v= st[v].next[t[i]];
                lens[i+1]=st[v].idx+1 ;
            }else{
                break;
            }
        }
        if(lens[m]){
            ++ans;
            continue;
        }
        for1(i,m){
            if(lens[i]){
                int falta;
                int v= 0;
                int j=m-1;

                for(; j>=i; --j){
                    if(st2[v].next.count(t[j])){
                        v= st2[v].next[t[j]];
                    }else{
                        break;
                    }
                }
                if(j==i-1 && (st2[v].idx > lens[i])){
                    ++ans;
                    break;
                }
            }
        }
    }
    cout<<ans<<el;
}
