#include <algorithm>
#include <vector>

struct DSU {
    std::vector<int> parent, subtree_size;
    DSU(int n) {
        parent.assign(n, -1);
        subtree_size.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int get_parent(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = get_parent(parent[v]);
    }
    void unite(int a, int b) {
        int pa = get_parent(a), pb = get_parent(b);
        if (pa == pb) {
            return;
        }
        if (subtree_size[pa] < subtree_size[pb]) {
            parent[pa] = pb;
        } else if (subtree_size[pa] > subtree_size[pb]) {
            parent[pb] = pa;
        } else {
            parent[pb] = pa;
            subtree_size[pa]++;
        }
    }
};