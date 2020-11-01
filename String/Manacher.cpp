// Longest Palindromic Substring
int manacher (string str) { // O(n)
	int len = (s.length() << 1) | 1;
	vector<int> z(len);
	string s(len, '$');
	for (int i = 1; i < len; i += 2)
		s[i] = str[i >> 1];
	int r = 0, p = 0, ans = 0;
	for (int i = 0, j = p << 1; i < len; i++, j--) {
		z[i] = (i >= r) ? 1 : min(z[j], r - i +1);
		while(0 <= i - z[i] && i + z[i] < len && s[i - z[i]] == s[i + z[i]])
			z[i]++;
		if (r < i + z[i] - 1)
			r = i + z[i] - 1, p = i;
		ans = max(ans, z[i]);
	}
	return ans - 1;
}