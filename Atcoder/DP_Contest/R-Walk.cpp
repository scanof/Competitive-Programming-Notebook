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

const int mod = 1e9 +7;

#define MAX_N 51 // Fibonacci matrix, increase/decrease this value as needed
struct Matrix { int mat[MAX_N][MAX_N]; }; // we will return a 2D array

Matrix matMul(Matrix a, Matrix b) { // O(n^3)
    Matrix ans; int i, j, k;
    for (i = 0; i < MAX_N; i++)
        for (j = 0; j < MAX_N; j++)
            for (ans.mat[i][j] = k = 0; k < MAX_N; k++){
                ans.mat[i][j] += (1LL*a.mat[i][k] * b.mat[k][j])%mod ; // modulo arithmetic
                ans.mat[i][j]%=mod;
            }
    return ans;
}

Matrix matPow(Matrix base, ll p) { // O(n^3 log p)
    Matrix ans; int i, j;
    for (i = 0; i < MAX_N; i++) for (j = 0; j < MAX_N; j++)
        ans.mat[i][j] = (i == j); // prepare identity matrix
    while (p) { // iterative version of Divide & Conquer exponentiation
        if (p & 1) ans = matMul(ans, base); // if p is odd (last bit is on)
        base = matMul(base, base); // square the base
        p >>= 1; // divide p by 2
    }
    return ans;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cout<< setprecision(2)<< fixed;
    int n;
    ll k;
    cin>> n>> k;
    Matrix m = Matrix();
    forn(i,n){
        forn(j,n){
            cin>> m.mat[i][j];
        }
    }
    Matrix z = matPow(m,k);
    ll suma= 0;
    forn(i,n)
        forn(j,n){
            suma+= z.mat[i][j]%mod;
            suma%=mod;
        }
    cout<< suma<<el;
}
