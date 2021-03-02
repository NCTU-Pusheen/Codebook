void heaps(int k, vector<int> &s, int n) {
	if (k == 1) {
		// for (int i = 0; i < n; i++)
		// 	cout << s[i] << " \n"[i == n - 1];
		return;
	}
	for (int i = 0; i < k - 1; ++i) {
		heaps(k - 1, s, n);
		if (k & 1) swap(s[i], s[k - 1]);
		else swap(s[0], s[k - 1]);
	}
	heaps(k - 1, s, n);
}
void permutation(int n) {
	vector<int> v(n);
	for (int i = 0; i < n; i++) v[i] = i;
	heaps(n, v, n);
}