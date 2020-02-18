#include <bits/stdc++.h>

#define fi first
#define se second
#define forn(i,n) for(int i=0; i<n; ++i)
#define for1(i,n) for(int i=1; i<=n; ++i)
#define fore(i,l,r) for(int i=l; i<=r; ++i)
#define pb push_back
#define el '\n'
#define d(x) cout<< #x<< " "<< x<< el
using namespace std;

typedef long long ll;
const int K= 26;
const int MAXN= 2e5+20;

struct state{
    int len, link;
    map<char,int> next;

};

state st[MAXN*2];
int sz , last;

void sa_init(){
    st[0].len=0;
    st[0].link=-1;
    ++sz;
    last=0;
}

void sa_extend(char c){
    int cur = sz++;
    st[cur].len= st[last].len +1;
    int p= last;
    while(p!= -1 && !st[p].next.count(c)){
        st[p].next[c]= cur;
        p = st[p].link;
    }
    if(p==-1){
        st[cur].link=0;
    }else{
        int q= st[p].next[c];
        if(st[p].len+1 == st[q].len){
            st[cur].link=q;
        }else{
            int clone = sz++;
            st[clone].len = st[p].len+1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while(p!=-1 && st[p].next[c]==q){
                st[p].next[c]=clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link= clone;

        }
    }
    last= cur;
}
string texto;
int n;
string pat;
int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    sa_init();
    cin>> texto;
    forn(i, texto.size()){
        sa_extend(texto[i]);
    }
    cin>> n;
    int ans;
    forn(i,n){
        int v= 0, l=0;
        ans=0;
        cin>> pat;
        for(int j=0; j< pat.size();){
            ++ans;
            int cont= 0;
            v=0;
            if(!st[v].next.count(pat[j])){
                ans=-1;
                break;
            }
            while(j< pat.size() && st[v].next.count(pat[j])){
                v= st[v].next[pat[j]];
                cont++;
                j++;
            }

        }
        cout<< ans<<el;

    }

}

