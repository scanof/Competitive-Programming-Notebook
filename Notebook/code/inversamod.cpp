// O(mod)
const int mod;
int inv[mod];
void precalc(){
  inv[1] = 1;
  fore(i,2,mod-1) inv[i] = (mod - (mod/i) * inv[mod%i] % mod) % mod;
}

/////////////////////////////////////
ll inverse(ll a, ll m){
  ll x, y;
  ll g = gcde(a, m, x, y);
  if (g != 1) {
    cout << "No solution!";
    return -1;
  }else{
    x = (x % m + m) % m;
    return x;
  }
}
