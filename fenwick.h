#include <vector>

struct Fenwick {
    std::vector<long long> f;
    fenwick(int n) {
        f.assign(n + 1, 0);
    }
    void update(int i, long long add) {
        for (i; i < f.size(); i = (i | (i + 1))) {
            f[i] += add;
        }
    }
    long long prefix_sum(int r) {
        long long s = 0;
        for (r; r >= 0; r = (r & (r + 1)) - 1) {
            s += f[r];
        }
        return s;
    }
    long long sum(int l, int r) {
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};