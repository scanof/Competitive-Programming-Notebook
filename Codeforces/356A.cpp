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

const int MAXN = 3e5+200;

int hijos[MAXN];

struct seg{
    vi t;

    void build(int v, int l, int r){
        if(l==r){
            hijos[l]= v;
            return ;
        }
        int mid = (l+r)>>1;
        build(v<<1, l, mid);
        build(v<<1|1, mid+1, r);
    }

    seg(int n){
        t = vi(n*4, -1);
        build(1, 0, n-1);
    }

    void put(int v, int tl, int tr, int l, int r, int x){
        if(l>r) return ;
        if(t[v]!=-1){
            if(t[v]>=tl && t[v]<=tr && (t[hijos[t[v]]]==-1 || t[hijos[t[v]]]== t[v])){
                t[hijos[t[v]]]= x;
            }
            return ;
        }
        if(tl== l && tr == r){
            if(t[v]==-1){
                t[v] = x;
            }else if(t[v]>=tl && t[v]<=tr && (t[hijos[t[v]]]==-1 || t[hijos[t[v]]]== t[v])){
                t[hijos[t[v]]]= x;
            }
            return ;
        }
        int mid = (tl+tr)>>1;
        put(v<<1, tl, mid, l, min(r, mid),x);
        put(v<<1|1, mid+1, tr, max(l,mid+1), r,x);
    }

    int query(int v, int tl, int tr, int pos, int val){
        if(tl==tr){
            return ((t[v]==-1 || t[v]==pos) ? val : t[v]);
        }
        if(t[v]!=-1 && t[v]!=pos) val = t[v];

        int mid = (tl+tr)>>1;
        if(pos<=mid){
            return query(v<<1,tl, mid,pos, val);
        }else{
            return query(v<<1|1, mid+1, tr, pos, val);
        }
    }

};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, m;
    cin>> n>> m;
    int l, r, x;
    seg st = seg(n);
    forn(i,m){
        cin>> l>> r>> x;
        --l, --r, --x;
        st.put(1, 0, n-1, l, r, x);
    }

    forn(i,n){
        cout<< st.query(1, 0, n-1, i, -1) + 1<<" ";
    }
    cout<<el;
}

