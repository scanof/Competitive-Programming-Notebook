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

const int MAXN = 1e5+200;

vi arr;

struct ST{
    int n;
    vi t;
    int pisos;
    ST(){}
    ST(int n){
        t.resize(n<<2);
        pisos = log2(n);
        build(1,0, n-1, 0);
    }
    void build(int v, int tl, int tr, int piso){
        if(tl==tr){
            t[v]= arr[tl];
            return ;
        }
        int tm = (tl+ tr)>>1;
        build(v<<1, tl, tm, piso + 1);
        build(v<<1|1, tm+1, tr, piso+1);
        if((pisos-piso)%2 == 0){
            t[v] = t[v<<1] ^ t[v<<1|1];
        }else{
            t[v] = t[v<<1] | t[v<<1|1];
        }
    }

    int query(int v, int tl, int tr, int l, int r){
        if(l>r) return 0;
        if(l==tl && r== tr) return t[v];
        int tm= (tl+ tr)>>1;
        int ans = 0;
        return query(v<<1, tl, tm, l, min(r,tm)) |
            query(v<<1|1, tm+1, tr, max(l,tm+1), r);
    }

    void update(int v, int tl, int tr, int pos, int val, int piso= 0){
        if(tl==tr){
            t[v]= arr[tl] = val;
            return ;
        }
        int tm = (tl+ tr)>>1;
        if(pos<= tm){
            update(v<<1, tl, tm, pos, val, piso+1);
        }else{
            update(v<<1|1, tm+1, tr, pos, val, piso+1);
        }
        if((pisos-piso)%2 == 0){
            t[v] = t[v<<1] ^ t[v<<1|1];
        }else{
            t[v] = t[v<<1] | t[v<<1|1];
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>> n;
    n= 1<<n;
    int q;
    cin>> q;
    arr.resize(n);
    forn(i,n) cin>> arr[i];
    ST st = ST(n);
    int pos, val;
    while(q--){
        cin>> pos>> val;
        st.update(1,0,n-1,pos-1,val);
        cout<< st.query(1,0,n-1,0,n-1)<<el;
    }


}


