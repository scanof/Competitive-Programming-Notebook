int binpow(int b, int e) {
	int ans = 1;
	for (; e; b = 1LL*b*b%mod, e /= 2)
		if (e&1) ans = 1LL*ans*b%mod;
	return ans;
}
