// KMP fail function.
int* kmp_fail(string& s) {
    int* f = new int[s.size()];
    int p = f[0] = -1;
    for (int i = 1; s[i]; i++) {
        while (p != -1 && s[p + 1] != s[i]) p = f[p];
        if (s[p + 1] == s[i]) p++;
        f[i] = p;
    }
    return f;
}

// Queries the counts sub appears in str.
int kmp_count(string& str, string& sub) {
    int* fail = kmp_fail(sub);
    int p = -1, ret = 0;
    for (int i = 0; i < str.size(); i++) {
        while (p != -1 && sub[p + 1] != str[i]) p = fail[p];
        if (sub[p + 1] == str[i]) p++;
        if (p == sub.size() - 1) p = fail[p], ret++;
    }
    delete[] fail;
    return ret;
}

// Queries the first index where sub appears in str; -1 indicates no matching.
int kmp(string& str, string& sub) {
    int* fail = kmp_fail(sub);
    int i, j = 0;
    while (i < str.size() && j < sub.size()) {
        if (sub[j] == str[i])
            i++, j++;
        else if (j == 0)
            i++;
        else
            j = fail[j - 1] + 1;
    }
    delete[] fail;
    return j == sub.size() ? (i - j) : -1;
}