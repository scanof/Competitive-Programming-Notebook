int mu[nax], f[nax], h[nax];
void pre(){
  mu[0] = 0; mu[1] = 1;
  for(int i = 1; i<nax; ++i){
    if(mu[i]==0) continue;
    for(int j= i+i; j<nax; j+=i){
      mu[j] -= mu[i];
    }
  }

  for(int i = 1; i < nax; ++i){
    for(int j = i; j < nax; j += i){
      f[j] += h[i]*mu[j/i];
    }
  }
}
////////
void pre(){
  mu[0] = 0; mu[1] = 1;
  fore(i,2,N){
    if (lp[i] == 0) {
      lp[i] = i; mu[i] = -1;
      pr.pb(i);
    }
    for (int j=0, mult= i*pr[j]; j<sz(pr) && pr[j]<=lp[i] && mult<=N; ++j, mult= i*pr[j]){
      if(i%pr[j]==0) mu[mult] = 0;
      else mu[mult] = mu[i]*mu[pr[j]];
      lp[mult] = pr[j];
    }
  }
}
