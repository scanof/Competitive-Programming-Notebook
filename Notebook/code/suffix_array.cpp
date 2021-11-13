struct SuffixArray { // test line 11
	vi sa, lcp;
	SuffixArray(string& s, int lim=256){
		int n = sz(s) + 1, k = 0, a, b;
		s.pb('$');
		vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j;
//      iota(all(y), n - j);
//			forn(i,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			forn(i,n) y[i] = (sa[i] - j >= 0 ? 0 : n) + sa[i]-j; // this replace the two lines
			// before hopefully xd
			fill(all(ws), 0);
			forn(i,n) ws[x[i]]++;
			for1(i,lim-1) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			for1(i,n-1) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for1(i,n-1) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k) // lcp(i): lcp suffix i-1,i
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};
