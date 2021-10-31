#include <vector>
#include <algorithm>

struct segtree {
	std::vector<long long> t, to_add;
	segtree(int n) {
		t.assign(4 * n + 4, 0);
		to_add.assign(4 * n + 4, 0);
	}
	int lson(int v) {
		return 2 * v + 1;
	}
	int rson(int v) {
		return 2 * v + 2;
	}
	void push(int v, int l, int r) {
		if (lson(v) < t.size()) {
			to_add[lson(v)] += to_add[v];
		}
		if (rson(v) < t.size()) {
			to_add[rson(v)] += to_add[v];
		}
		t[v] += (r - l) * to_add[v];
		to_add[v] = 0;
	}
	long long get(int v, int l, int r) {
		if (v >= t.size()) {
			return 0;
		}
		return t[v] + to_add[v] * (r - l);
	}
	void update(int v, int l, int r, int i, long long x) {
		if (i < l || i >= r) {
			return;
		}
		if (l == r - 1) {
			t[v] = x;
			return;
		}
		push(v, l, r);
		int mid = (l + r) / 2;
		update(lson(v), l, mid, i, x);
		update(rson(v), mid, r, i, x);
		t[v] = get(lson(v), l, mid) + get(rson(v), mid, r);
	}
	void add_on_segment(int v, int l, int r, int ql, int qr, long long add) {
		if (l >= qr || ql >= r) {
			return;
		}
		if (ql <= l && r <= qr) {
			to_add[v] += add;
			return;
		}
		push(v, l, r);
		int mid = (l + r) / 2;
		add_on_segment(lson(v), l, mid, ql, qr, add);
		add_on_segment(rson(v), mid, r, ql, qr, add);
		t[v] = get(lson(v), l, mid) + get(rson(v), mid, r);
	}
	long long get_sum(int v, int l, int r, int ql, int qr) {
		push(v, l, r);
		if (l >= qr || ql >= r) {
			return 0;
		}
		if (ql <= l && r <= qr) {
			return get(v, l, r);
		}
		int mid = (l + r) / 2;
		auto s1 = get_sum(lson(v), l, mid, ql, qr);
		auto s2 = get_sum(rson(v), mid, r, ql, qr);
		t[v] = get(lson(v), l, mid) + get(rson(v), mid, r);
		return s1 + s2;
	}
};