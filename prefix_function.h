#include <vector>
#include <string>

std::vector<int> prefix_function(std::string s) {
    std::vector<int> p(s.size(), 0);
	for (int i = 1; i < p.size(); ++i) {
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k]) {
			k = p[k - 1];
		}
		if (s[i] == s[k]) {
			++k;
		}
		p[i] = k;
	}
    return p;
}