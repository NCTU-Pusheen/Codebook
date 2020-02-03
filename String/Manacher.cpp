// Longest Palindromic Substring
int manacher (char *str) {
	int len = (strlen(str) << 1) | 1;
	int *z = new int[len](); // 以s[i]為軸的最大對稱半徑
	char *s = new char[len];
	memset(s, '$', len);
	for (int i = 1; i < len; i += 2)
		s[i] = str[i >> 1];
	int r = 0; // 最右界
	int p = 0; // 對稱軸
	int ans = 0;
	for (int i = 0; i < len; i++) {
		int ii = 2 * p - i; // i以p為軸映射
		if (i >= r) z[i] = 1;
		else z[i] = min(z[ii], r - i + 1);
		while (0 <= i-z[i] && i+z[i] < len && s[i-z[i]] == s[i+z[i]])
			z[i]++;
		if (r < i + z[i] - 1)
			r = i + z[i] - 1, p = i;
		ans = max(ans, z[i]);
	}
	delete [] s, delete [] z;
	return ans - 1;
}