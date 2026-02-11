#include "../../template.h"

// UVA 1184 - AC
// https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&category=246&page=show_problem&problem=3625
vector<int> g[nax]; // [0,n)->[0,m)
int n,m;
int mat[MAXM];bool vis[nax];
int match(int x){
  if(vis[x])return 0;
  vis[x]=true;
  for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
  return 0;
}
vector<pair<int,int> > max_matching(){
  vector<pair<int,int> > r;
  memset(mat,-1,sizeof(mat));
  fore(i,0,n)memset(vis,false,sizeof(vis)),match(i);
  fore(i,0,m)if(mat[i]>=0)r.pb({mat[i],i});
  return r;
}

int main(){
  int tn;
  scanf("%d",&tn);
  while(tn--){
    int e;
    scanf("%d%d",&n,&e);m=n;
    while(e--){
      int x,y;
      scanf("%d%d",&x,&y);x--;y--;
      g[x].pb(y);
    }
    printf("%d\n",n-SZ(max_matching()));
    fore(i,0,n)g[i].clear();
  }
  return 0;
}
