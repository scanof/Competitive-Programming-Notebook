typedef long double ld;
const ld PI = acos(-1.0L);
struct pt {
  double r, i;
  pt(double r = 0.0, double i = 0.0) : r(r), i(i) {}
  pt operator + (const pt & b) { return pt(r + b.r, i + b.i); }
  pt operator - (const pt & b) { return pt(r - b.r, i - b.i); }
  pt operator * (const pt & b) { return pt(r * b.r - i * b.i, r * b.i + i * b.r); }
  pt operator / (const pt & b) { double k = b.r*b.r+b.i*b.i; return pt((r*b.r +(i*b.i)) / k, (-r*b.i + i*b.r) / k);}
  pt operator / (double k) { return pt(r /k , i / k);}
  pt conj(){ return pt(r, -i);}
  pt polar(ld a, ld b){
    return pt(0,0);
  }
};

//typedef complex<double> C;
typedef vector<double> vd;

pt polarfft(ld rho, ld theta){
//  return pt(rho * cos(theta), rho * sin(theta));
  return pt(cos(theta), sin(theta));
}

void fft(vector<pt>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<pt> R(2, 1);
	static vector<pt> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		pt x = polarfft(1.0L,PI / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
//			pt z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			pt z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] = a[i+j] + z;
		}
}

typedef vector<ll> vl;

vl conv(const vl& a, const vl& b) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<pt> in(n), out(n);
  forn(i,sz(a)) in[i].r = a[i];
	rep(i,0,sz(b)) in[i].i =  b[i];
	fft(in);
	for (pt& x : in) x = x* x;
	rep(i,0,n){
	  out[i] = in[-i & (n - 1)] - in[i].conj();
	}
	fft(out);
	rep(i,0,sz(res)){
	  res[i] = out[i].i / (4 * n) +0.5;
	}
	return res;
}

vl convMod(const vl &a, const vl &b, int M) {
	if (a.empty() || b.empty()) return {};
	vl res(sz(a) + sz(b) - 1);
	int B=32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(M));
	vector<pt> L(n), R(n), outs(n), outl(n);
	rep(i,0,sz(a)) L[i] = pt((int)a[i] / cut, (int)a[i] % cut);
	rep(i,0,sz(b)) R[i] = pt((int)b[i] / cut, (int)b[i] % cut);
	fft(L), fft(R);
	rep(i,0,n) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + L[j].conj()) * R[i] / (2.0 * n);
		outs[j] = (L[i] - L[j].conj()) * R[i] / (2.0 * n) / pt(0,1);
	}
	fft(outl), fft(outs);
	rep(i,0,sz(res)) {
		ll av = ll(outl[i].r+.5), cv = ll(outs[i].i+.5);
		ll bv = ll(outl[i].i+.5) + ll(outs[i].r+.5);
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
