void z_build(string &s, vector<int> &z) {
    int bst = z[0] = 0;
    for (int i = 1; s[i]; i++) {
        if (z[bst] + bst < i) z[i] = 0;
        else z[i] = min(z[bst] + bst - i, z[i - bst]);
        while (s[z[i]] == s[i + z[i]]) z[i]++;
        if (z[i] + i > z[bst] + bst) bst = i;
    }
}
// Queries how many times s appears in t
int z_match(string &s, string &t) {
    int ans = 0;
    int lens = s.length(), lent = t.length();
    vector<int> z(lens + lent + 1);
    string st = s + "$" + t;
    z_build(st, z);
    for (int i = lens + 1; i <= lens + lent; i++)
        if (z[i] == lens) ans++;
    return ans;
}
