int phi(int n) {
	vector<int> p = factor(n);
	for (int i = 0; i < (int) p.size(); i++) {
		if (i && p[i] == p[i - 1])
			continue;
		n /= p[i];
		n *= p[i] - 1;
	}
	return n;
}
