typedef pair<long long, long long> pt;
const int maxn = 1e6 + 10;
pt operator-(const pt& p1 , const pt& p2) {
    return pt(p1.x - p2.x, p1.y - p2.y);
}
long long cross(const pt& p1, const pt& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
long long dis(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
vector<pt> ch;
pt p[maxn];
double shoelace_formula(vector<pt> &v) {
    int n = v.size();
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += (v[i].x * v[(i + 1) % n].y);
    for (int i = 0; i < n; i++)
        ans -= (v[i].y * v[(i + 1) % n].x);
    return abs(ans / 2);
}
double farthest_dis(vector<pt> &v) {
    int k = 1, n = v.size();
    long long ans = 0;
    if (n == 2) return dis(v[0], v[1]);
    for (int i = 0; i < n; i++) {
        while (llabs(cross(v[i] - v[(k + 1) % n], v[(i + 1) % n] - v[(k + 1) % n])) >= llabs(cross(v[i] - v[k], v[(i + 1) % n] - v[k])))
            k = (k + 1) % n;
        ans = max(ans, max(dis(v[i], v[k]), dis(v[(i + 1) % n], v[k])));
    } return sqrt(ans);
}
int n;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    sort(p, p + n);
    for (int i = 0; i < n; i++) {
        while (ch.size() >= 2 && cross(ch[ch.size() - 1] - ch[ch.size() - 2], p[i] - ch[ch.size() - 2]) <= 0)
            ch.pop_back();
        ch.push_back(p[i]);     
    }
    for (int i = n - 2, t = ch.size() + 1; i >= 0; i--) {
        while (ch.size() >= t && cross(ch[ch.size() - 1] - ch[ch.size() - 2], p[i] - ch[ch.size() - 2]) <= 0)
            ch.pop_back();
        ch.push_back(p[i]);
    }
    if (n >= 2) ch.pop_back();
    cout << setprecision(6) << fixed << shoelace_formula(ch) << '\n';
    cout << setprecision(6) << fixed << farthest_dis(ch) << '\n';
    return 0;
}
