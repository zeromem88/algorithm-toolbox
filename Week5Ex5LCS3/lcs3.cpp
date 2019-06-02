#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

static int T[101][101][101];

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
	//write your code here
	//return std::min(std::min(a.size(), b.size()), c.size());

	size_t s1, s2, s3;
	s1 = a.size();
	s2 = b.size();
	s3 = c.size();
	
	for (int i = 0; i <= s1; ++i) {
		T[i][0][0] = 0;
	}
	for (int j = 0; j <= s2; ++j) {
		T[0][j][0] = 0;
	}
	for (int k = 0; k <= s3; ++k) {
		T[0][0][k] = 0;
	}
	for (int k = 1; k <= s3; ++k) {
		for (int j = 1; j <= s2; ++j) {
			for (int i = 1; i <= s1; ++i) {
				if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
					T[i][j][k] = T[i - 1][j - 1][k - 1] + 1;
				}
				else {
					int case1 = T[i][j - 1][k];
					int case2 = T[i - 1][j][k];
					int case3 = T[i][j - 1][k - 1];
					int case4 = T[i - 1][j][k - 1];
					int case5 = T[i - 1][j - 1][k];
					int case6 = T[i][j][k - 1];
					T[i][j][k] = std::max(case1, std::max(case2, std::max(case3, std::max(case4, std::max(case5, case6)))));
				}
			}
		}
	}
	return T[s1][s2][s3];
}

int main() {
	size_t an;
	std::cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++) {
		std::cin >> a[i];
	}
	size_t bn;
	std::cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++) {
		std::cin >> b[i];
	}
	size_t cn;
	std::cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++) {
		std::cin >> c[i];
	}
	std::cout << lcs3(a, b, c) << std::endl;
}
