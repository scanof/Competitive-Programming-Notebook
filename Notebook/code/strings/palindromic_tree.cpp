struct palindromic_tree{
  static const int SIGMA = 26;
  struct node{
    int link, len, p, to[SIGMA];
    node(int len, int link=0,int p=0):
            len(len),link(link),p(p){
        memset(to,0,sizeof(to));
    }
  };
  int last;
  vector<node> st;
  palindromic_tree():last(0){fore(i,-1,0)st.pb(node(i));}

  void add(int i, const string &s){
    int c = s[i]-'a';
    int p = last;
    while(s[i-st[p].len-1]!=s[i]) p=st[p].link;

    if(st[p].to[c]){
      last = st[p].to[c];
    }else{
      int q=st[p].link;
      while(s[i-st[q].len-1]!=s[i]) q=st[q].link;
      q=max(1,st[q].to[c]);
      last = st[p].to[c] = sz(st);
      st.pb(node(st[p].len+2,q,p));
    }
  }
};
