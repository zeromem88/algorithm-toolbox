#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

static int T[101][101];

int lcs2(const vector<int> &a, const vector<int> &b) {
	size_t s1, s2;
	s1 = a.size();
	s2 = b.size();
	for (int i = 0; i <= s1; ++i) {
		T[i][0] = 0;
	}
	for (int j = 1; j <= s2; ++j) {
		T[0][j] = 0;
	}
	for (int j = 1; j <= s2; ++j) {
		for (int i = 1; i <= s1; ++i) {
			if (a[i - 1] == b[j - 1]) {
				T[i][j] = T[i - 1][j - 1] + 1;
			} else {
				int ins = T[i][j - 1];
				int dels = T[i - 1][j];
				T[i][j] = std::max(ins, dels);
			}
		}
	}
	return T[s1][s2];
	//write your code here
	//return std::min(std::min(a.size(), b.size()), c.size());
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
