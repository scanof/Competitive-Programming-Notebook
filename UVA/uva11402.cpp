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
const int MAXN = 1e5+200;

vi arr;

struct ST{
    vi t;
    vi lazy;
    vi hijos;
    int n;
    ST(){}
    ST(int n_){
        n= n_;
        hijos.resize(n<<2);
        t.resize(n<<2);
        lazy.resize(n<<2);
        build(1,0,n-1);
    }

    void build(int v, int tl, int tr){
        if(tl==tr){
            t[v]= arr[tl];
            hijos[v] = 1;
            return ;
        }
        int tm = (tl+tr)>>1;
        build(v<<1, tl, tm);
        build(v<<1|1, tm+1, tr);
        t[v]= t[v<<1] + t[v<<1|1];
        hijos[v] = hijos[v<<1] + hijos[v<<1|1];
    }

    void modif(int v, int l){
        if(l==1){
            t[v] = hijos[v];
        }else if(l==3){
            t[v] = hijos[v]- t[v];
        }else if(l==2){
            t[v] = 0;
        }
    }

    int combine(int a, int b){
        if(b==0) return a;
        if(a==1 || a==2){
            return a;
        }else{
            if(b==3) return 0;
            if(b==1) return 2;
            return 1;
        }
    }

    void push(int v){
        if(v>=4*n) return ;
        if(lazy[v]==0) return ;
        modif(v, lazy[v]);
        if(v<=2*n){
            lazy[v<<1] = combine(lazy[v],lazy[v<<1]);
            lazy[v<<1|1] = combine(lazy[v],lazy[v<<1|1]);
        }
        lazy[v] = 0;
        return ;
    }

    void update(int v, int tl, int tr, int l, int r, int laz) {
        push(v);
        if (l > r)
            return;
        if (l == tl && tr == r) {
            lazy[v] = combine(laz,lazy[v]);
            push(v);
        }else{
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), laz);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, laz);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        push(v);
        if (l > r)
            return 0;
        if (l <= tl && tr <= r){
            return t[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))+
                   query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL); cout.tie(NULL);
    int t;
    cin>> t;
    for1(tt,t){
        int n;
        cin>> n;
        int m;
        string s, tmp;
        forn(i,n){
            cin>> m >> tmp;
            while(m--){
                s+= tmp;
            }
        }
        arr.resize(s.size());
        forn(i,s.size()){
            arr[i]= s[i]-'0';
        }
        ST st = ST(s.size());
        int q;
        cin>> q;
        char ch;
        int l,r;
        cout<< "Case "<< tt<< ":\n";
        int queries = 1;
        n = s.size();
        while(q--){
            cin>> ch>> l>> r;
            // barbary is 0, buccaneer is 1
            if(ch=='F'){
                st.update(1, 0, n-1, l, r, 1);
            }else if(ch=='E'){
                // change to 0
                st.update(1, 0, n-1, l, r, 2);
            }else if(ch=='I'){
                // flip
                st.update(1, 0, n-1, l, r, 3);
            }else{
                cout<<"Q" << queries++ <<": "  <<st.query(1, 0, n-1, l, r)<<el;
            }
        }
    }

}

