#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

static unordered_map<long long, bool> memo;

bool doPart3(const vector<int> &A, int m, int n, int p, int l) {

	if (m == 0 && n == 0 && p == 0)
		return true;

	if (l < 0)
		return false;

	long long key = m * 100000000 + n * 10000 + p;

	const auto&& it = memo.find(key);
	if (it != memo.end())
		return it->second;

	if (m - A[l] >= 0 && doPart3(A, m - A[l], n, p, l - 1)) {
		memo[key] = true;
		return true;
	}

	if (n - A[l] >= 0 && doPart3(A, m, n - A[l], p, l - 1)) {
		memo[key] = true;
		return true;
	}

	if (p - A[l] >= 0 && doPart3(A, m, n, p - A[l], l - 1)) {
		memo[key] = true;
		return true;
	}

	memo[key] = false;

	return false;
}

int partition3(vector<int> &A) {

	int sum = 0;
	for (auto&& i : A) {
		sum += i;
	}
	if (sum % 3 != 0)
		return 0;
	sum = sum / 3;
	//write your code here
	return doPart3(A, sum, sum, sum, A.size() - 1);
}

int main() {
	int n;
	std::cin >> n;
	vector<int> A(n);
	for (size_t i = 0; i < A.size(); ++i) {
		std::cin >> A[i];
	}
	std::cout << partition3(A) << '\n';
}
