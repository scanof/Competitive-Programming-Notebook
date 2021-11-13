vi g[nax];
int son[nax], bro[nax];
void binarize(int u, int p = -1){
  bool flag = 0; int prev = 0;
  for(int v : g[u]){  
    if(v == p) continue; 
    if(flag) bro[prev] = v;
    else son[u] = v, flag = true;
    binarize(v, u);
    prev = v;
  }
}