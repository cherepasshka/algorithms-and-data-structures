#include <vector>
#include <cmath>

struct InOutStruct {
    std::vector<int> tin, tout;
    int timer;
    InOutStruct(int n) {
        tin.assign(n, 0);
        tout.assign(n, 0);
        timer = 0;
    }
};


void dfs(int v, const std::vector<std::vector<int>>& g, std::vector<int>& used, InOutStruct& s, std::vector<std::vector<int>>& up) {
    s.tin[v] = ++s.timer;
    used[v] = 1;
    for (int i = 1; i < up.size(); ++i) {
        int prev = up[i - 1][v];
        if (prev == -1) {
            continue;
        }
        up[i][v] = up[i - 1][prev];
    }
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to, g, used, s, up);
        }
    }
    s.tout[v] = ++s.timer;
}
bool upper(int a, int b, InOutStruct& s) {
    return s.tin[a] <= s.tin[b] && s.tout[b] <= s.tout[a];
}
int lca(int a, int b, InOutStruct& s, const std::vector<std::vector<int>>& up) {
    if (upper(a, b, s)) {
        return a;
    }
    if (upper(b, a, s)) {
        return b;
    }
    for (int i = up.size() - 1; i >= 0; --i) {
        int par = up[i][a];
        if (par == -1)continue;
        if (!upper(par, b, s)) {
            a = par;
        }
    }
    if (up[0][a] == -1)return a;
    return up[0][a];
}