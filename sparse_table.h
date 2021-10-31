#include <algorithm>
#include <vector>

struct SparseTable {
	std::vector<std::vector<int>> table;
	std::vector<int> lg;
	SparseTable(int n) {
		lg.assign(n + 1, 0);
		int l = 0;
		for (int i = 1; i <= n; ++i) {
			if ((1 << (l + 1)) == i) {
				++l;
			}
			lg[i] = l;
		}
		table.assign(lg[n] + 1, std::vector<int>(n, 1e9));
	}
	void build(const std::vector<int>& a) {
		for (int i = 0; i < a.size(); ++i) {
			table[0][i] = a[i];
		}
		for (int k = 1; k < table.size(); ++k) {
			for (int i = 0; i + (1 << (k - 1)) < a.size(); ++i) {
				table[k][i] = std::max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
			}
		}
	}
	int get_max(int l, int r) {
		int lg2 = lg[r - l + 1];
		return std::max(table[lg2][l], table[lg2][r - (1 << lg2) + 1]);
	}
};