#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i,n) for(int i=0; i< (int)n; ++i)
#define for1(i,n) for(ll i=1; i<= n; ++i)
#define fore(i,l,r) for(int i=(int)l; i<= (int)r; ++i)
#define ford(i,n) for(int i=(int)(n) - 1; i>= 0; --i)
#define fored(i,r,l) for(int i=(int)r; i>= (int)l; --i)
#define pb push_back
#define el '\n'
#define deb(x) cout<< #x<< " " << x<<el
#define INF (1LL<<62)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef tuple<int,int,int> ti;
const double PI = atan(1)*4;
const int MAXN = 1e5+20;

int a[MAXN];

ii combine(ii a, ii b){
    if(a.fi==-1) return b;
    if(b.fi==-1) return a;
    if(a.fi==b.fi){
        return ii(a.fi, b.se + a.se);
    }
    if(a.fi%b.fi==0){
        return b;
    }
    if(b.fi%a.fi==0){
        return a;
    }
    return ii(__gcd(a.fi,b.fi), 0);
}

struct segtree{
    vector<ii> t;

    void build(int v, int l, int r){
        if(l==r){
            t[v] = ii(a[l],1);
            return ;
        }
        int mid = (l+r)>>1;
        build(v<<1, l,mid );
        build(v<<1|1, mid+1, r);
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    segtree(int n){
        t = vector<ii>(4*n);
        build(1,0,n-1);
    }

    ii query(int v, int tl, int tr, int l, int r){
        if(l>r) return ii(-1, 0);
        if(tl==l && tr== r){
            return t[v];
        }
        int mid = (tl+tr)>>1;
        return combine(query(v<<1,tl, mid, l, min(r, mid)),
                       query(v<<1|1,mid+1, tr, max(l,mid+1),r));

    }


};


int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n;
    cin>> n;
    forn(i,n) cin>> a[i];
    segtree st = segtree(n);
    int t;
    cin>> t;
    int x, y;
    while(t--){
        cin>> x>> y;
        x-- , y--;
        cout<< (y-x+1)-st.query(1,0,n-1,x,y).se<<el;
    }

}
