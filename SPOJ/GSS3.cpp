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

const ll INF = 1e17;
const int MAXN = 5e4+200;
const double PI = acos(-1);
const double EPS= 1e-10;

int dr[] = {1,-1,0, 0,1,-1,-1, 1}; // trick to explore an implicit 2D grid
int dc[] = {0, 0,1,-1,1, 1,-1,-1};

int arr[MAXN];

struct node{
    ll pre, su, sum, ans;
    node(){
        pre= su = sum = ans = -INF;
    }
};

node combine(node a, node b){
    node c = node();
    c.sum = a.sum+ b.sum;
    c.pre = max(a.sum+ b.pre, a.pre);
    c.su = max(b.sum+ a.su, b.su);
    c.ans = max(c.pre, c.su);
    c.ans = max(c.sum, c.ans);
    c.ans = max(a.su + b.pre, c.ans);
    c.ans = max(b.ans, c.ans);
    c.ans = max(a.ans, c.ans);
    return c;
}

struct seg{
    vector<node> t;

    void build(int v, int l, int r){
        if(l==r){
            t[v] = node();
            t[v].sum = arr[l];
            t[v].ans = t[v].pre =t[v].su = arr[l];
            return ;
        }
        int mid = (l+r)>>1;
        build(v<<1, l, mid);
        build(v<<1|1, mid+1, r);
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    seg(int n){
        t = vector<node>(n*4);
        build(1, 0, n-1);
    }

    node query(int v, int tl, int tr, int l, int r){
        if(l>r){
            node a = node();
            return a;
        }
        if(tl==l && tr==r){
            return t[v];
        }
        int mid = (tl+tr)>>1;
        return combine(query(v<<1, tl, mid, l, min(r,mid)), query(v<<1|1, mid+1 , tr, max(l,mid+1) , r));
    }

    void update(int v, int tl, int tr, int pos, int val){
        if(tl==tr){
            t[v] = node();
            t[v].sum = val;
            t[v].ans = t[v].pre =t[v].su = val;
            return ;
        }
        int mid = (tl+tr)>>1;
        if(pos<=mid){
            update(v<<1, tl, mid, pos, val);
        }else{
            update(v<<1|1, mid+1, tr, pos, val);
        }
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n;
    cin>>n;
    forn(i,n){
        cin>> arr[i];
    }
    seg st = seg(n);
    int q;
    cin>> q;
    int op, x, y;
    while(q--){
        cin>> op>> x>> y;
        --x;
        if(op==1){
            --y;
            cout<< st.query(1,0,n-1,x,y).ans<<el;
        }else{
            st.update(1,0,n-1,x,y);
        }
    }
}
