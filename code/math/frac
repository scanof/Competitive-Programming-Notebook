struct frac{
  ll num, den;
  frac(){}
  frac(ll num, ll den):num(num), den(den){ 
    if(!num) den = 1;
    if(num > 0 && den < 0) num = -num,  den = -den;
    simplify(); 
  }
  void simplify(){
    ll g = __gcd(abs(num), abs(den));
    if(g) num /= g,  den /= g;
  }
  frac operator+(const frac& b){ return {num*b.den + b.num*den, den*b.den};}
  frac operator-(const frac& b){ return {num*b.den - b.num*den, den*b.den};}
  frac operator*(const frac& b){ return {num*b.num, den*b.den};}
  frac operator/(const frac& b){ return {num*b.den, den*b.num};}
  bool operator<(const frac& b)const{ return num*b.den < den*b.num; }
};
