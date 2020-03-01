#include <bits/stdc++.h>
using namespace std;

vector<int> g[100005];
int seen[100005];
int scc=0;
int comp[100005];

void dfs(int u){
    seen[u]=1;
    comp[scc]++;
    for(int i=0; i< g[u].size(); ++i){
        int v= g[u][i];
        if(!seen[v]) dfs(v);
    }
}

void call_dfs(int n){
    for(int i=0; i<n; ++i){
        seen[i]=0;
        comp[i]=0;
    }
    for(int i=0; i<n; ++i){
        if(!seen[i]){
            dfs(i);
            scc++;
        }
    }
}

int main(){
    long long n,p,temp1,temp2;
    cin>> n >> p;
    for(int i=0; i<p; ++i){
        cin>> temp1>> temp2;
        g[temp1].push_back(temp2);
        g[temp2].push_back(temp1);
    }
    call_dfs(n);
    long long ans=0;
    ans+= n*(n-1)/2;
    for(int i=0;i<scc; ++i){
        ans-= comp[i]*(comp[i]-1)/2;
    }
    cout<< ans<<endl;
}
