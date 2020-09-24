#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges;
vector<bool> visit;
vector<int> match;


bool dfs(int from) {
    for(int next : edges[from]) {
        if(visit[next]) continue;
        visit[next] = 1;
        if(match[next] == -1 || dfs(match[next])) {
            match[next] = from;
            match[from] = next;
            return true;
        }
    }
    return false;
}

int hungarian(int p, int q) {
    int ans = 0;

    for(int i = 0;i < p;i++) {
        if(match[i] == -1) {
            visit.assign(visit.size(), 0);
            if(dfs(i)) ans += 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false) ,cin.tie(0) ,cout.tie(0);
    int p, q, k; // 有 p 個紅點， q 個藍點， 和 k 條邊 
    cin >> p >> q >> k;
    edges.resize(p + 5);
    match.resize(p + q + 5, -1);
    visit.resize(p + q + 5, false);
    for(int i = 0; i < k; i++) {
        int eax, ebx;
        cin >> eax >> ebx;
        eax --; ebx --;
        ebx += p;
        edges[eax].push_back(ebx);
    }
    cout << hungarian(p, q) << endl;
    edges.clear();
    visit.clear();
    match.clear();
}
