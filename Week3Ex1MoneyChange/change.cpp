#include <iostream>

int get_change(int m) {
	int n = 0;
	int t;

	while ((t = m - 10) >= 0) {
		m = t;
		++n;
	}

	while ((t = m - 5) >= 0) {
		m = t;
		++n;
	}

	while ((t = m - 1) >= 0) {
		m = t;
		++n;
	}

	return n;
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
