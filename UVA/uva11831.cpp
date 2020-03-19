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

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<char,int> pci;
typedef tuple<int, int, int> tiii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

int dr[] = {0,-1, 0,1}; // trick to explore an implicit 2D grid
int dc[] = {-1,0,1,0};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n, m, s;
    while(cin>>n>>m >> s){
        if(n+m+s==0) return 0;
        string grid[n];
        int x, y, mov;
        forn(i,n){
            cin>> grid[i];
            forn(j,m)
                if(grid[i][j]=='N'){
                    x= i; y= j; mov= 0;
                }else if(grid[i][j]=='L'){
                    x= i; y= j; mov=3;
                }else if(grid[i][j]=='S'){
                    x= i; y= j; mov=2;
                }else if(grid[i][j]=='O'){
                    x= i; y= j; mov=1;
                }
        }
        string ins;
        cin>> ins;
        int ans= 0;
        forn(i,s){
            if(ins[i]=='D'){
                --mov;
                (mov+=4)%=4;
            }else if(ins[i]=='E'){
                ++mov;
                mov%=4;
            }else if(ins[i]=='F'){
                if(x+ dc[mov]>=0 && x+ dc[mov]<n && y+ dr[mov]>=0 && y+ dr[mov]<m){
                    char ch = grid[x+dc[mov]][y+dr[mov]];
                    if(ch!='#'){
                        x+=dc[mov]; y+= dr[mov];
                        if(ch=='*'){
                            ++ans;
                        }
                        grid[x][y]='o';
                    }

                }
            }

        }
        cout<< ans<<el;
    }
}
