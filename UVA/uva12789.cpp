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

struct dsu{
    vi p, r;
    vector<bool> up, down;
    void init(int n){
        r.assign(n,1); p.assign(n,0);
        up.assign(n, false);  down.assign(n, false);
        forn(i,n) p[i]= i;
    }
    int findSet(int i){
        return (p[i]==i) ? i : (p[i]= findSet(p[i]));
    }

    void unionSet(int i, int j){
        int x = findSet(i), y = findSet(j);
        if(up[x] || up[i] || up[y] || up[j]) up[x]= up[i]=up[y]= up[j]= true;
        if(down[x] || down[i] || down[y] || down[j]) down[x] = down[i]=down[y] = down[j]= true;
        if(x!=y){
            if(r[x]> r[y]){
                p[y] = x;
                r[x]+= r[y]; r[y]= 0;
            }else{
                p[x]= y;
                r[y]+= r[x]; r[x]= 0;
            }
//            if(up[x] || up[y]) up[x]= up[y]= true;
//            if(down[x] || down[y]) down[x] = down[y]= true;
//            --numSets;
        }
    }

};

int dr[] = {0, 1, 0, -1};
int dc[] = {1, 0, -1, 0};

int nax = 1000;

int conv(int i, int j){
    return i*nax + j;
}

dsu uf;

int main(){
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
//    cout<< setprecision(2)<<fixed;
    int n, m, q;
    while(cin>> n>> m>> q){
        char grid[n][m];
        forn(i,n){
            forn(j,m){
                cin>> grid[i][j];
            }
        }
        nax = max(n,m)+1;
        uf.init(nax*nax);
        bool works = false;
        forn(i,n){
            forn(j,m){
                if(i==0){
                    uf.up[conv(i,j)]= true;
                }
                if(i==n-1){
                    uf.down[conv(i,j)]= true;
                }
                if(grid[i][j]=='#') continue;
                forn(k,8){
                    int nx = dr[k%4]+ i, ny = dc[k%4]+j;
                    if(nx<n && nx>=0 && ny<m && ny>=0 && grid[nx][ny]=='.'){
                        uf.unionSet(conv(i,j), conv(nx, ny));
                    }
                }
                if(uf.down[conv(i,j)] && uf.up[conv(i,j)]){
                    works = true;
                    break;
                }
            }
            if(works) break;
        }
        if(works){
            cout<< 0<< el;
        }
        int y, c;
        for1(test,q){
            cin>> c;
            y= c;
            if(works) continue;
            if(y<0){
                c=-1;
                y= abs(y);
                y--;
                int x = n-1;
                while(x>=0 && grid[x][y]=='.'){
                    --x;
                }
                if(x<0) continue;
                grid[x][y]= '.';
                forn(k,8){
                    int nx = dr[k%4]+ x, ny = dc[k%4]+y;
                    if(nx<n && nx>=0 && ny<m && ny>=0 && grid[nx][ny]=='.'){
                        uf.unionSet(conv(x,y), conv(nx, ny));
                    }

                }
                if(uf.up[conv(x,y)] && uf.down[conv(x,y)]){
                    works = true;
                    cout<< test*c<<el;
                }
                continue;
            }
            c= 1;
            y--;
            int x = 0;
            while(x<=n-1 && grid[x][y]=='.'){
                ++x;
            }
            if(x>n-1) continue;
            grid[x][y]= '.';
            forn(k,8){
                int nx = dr[k%4]+ x, ny = dc[k%4]+y;
                if(nx<n && nx>=0 && ny<m && ny>=0 && grid[nx][ny]=='.'){
                    uf.unionSet(conv(x,y), conv(nx, ny));
                }
            }
            if(uf.up[conv(x,y)] && uf.down[conv(x,y)]){
                works = true;
                cout<< test*c<<el;
            }
        }
        if(!works){
            cout<< "X"<<el;
        }
    }
}
