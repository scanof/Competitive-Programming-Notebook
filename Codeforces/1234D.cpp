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

int conv(char ch){
    return ch-'a';
}

struct node{
    int next[26];
    int ans;
    node(){
        ans = 0;
        memset(next, 0, sizeof next);
    }
};

node combine(node a, node b){
    node c= node();
    forn(i,26){
        c.next[i] = a.next[i] + b.next[i];
        if(c.next[i]) ++c.ans;
    }
    return c;
}

string s;

struct seg{
    vector<node> t;

    void build(int v, int l, int r){
        if(l==r){
            t[v] = node();
            t[v].next[conv(s[l])]++;
            t[v].ans = 1;
            return ;
        }
        int mid = (l+r)>>1;
        build(v<<1, l, mid);
        build(v<<1|1, mid+1, r);
        t[v] = combine(t[v<<1], t[v<<1|1]);
    }

    seg(int n){
        t = vector<node>(4*n);
        build(1, 0, n-1);
    }

    node query(int v, int tl, int tr, int l, int r){
        if(l>r) return node();
        if(tl==l && tr == r) return t[v];
        int mid = (tl+tr)>>1;
        return combine(query(v<<1,tl, mid, l, min(r,mid)), query(v<<1|1, mid+1, tr, max(l,mid+1),r));
    }

    void update(int v, int tl, int tr, int pos, char ch){
        if(tl==tr){
            t[v]= node();
            t[v].next[conv(ch)]++;
            t[v].ans = 1;
            return ;
        }
        int mid = (tl+tr)>>1;
        if(pos<=mid){
            update(v<<1, tl, mid, pos, ch);
        }else{
            update(v<<1|1, mid+1, tr, pos, ch);
        }
        t[v]= combine(t[v<<1], t[v<<1|1]);
    }

};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    cin>>s;
    int q;
    cin>> q;
    int op;
    int n= s.size();
    seg st = seg(n);
    forn(i,q){
        cin>> op;
        if(op==1){
            int x; char ch;
            cin>> x>> ch;
            st.update(1,0,n-1,x-1,ch);
        }else{
            int x, y;
            cin>> x>> y;
            x--, y--;
            cout<< st.query(1,0,n-1,x,y).ans<<el;
        }

    }
}
