#include <iostream>

int get_fibonacci_last_digit_naive(int n) {
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
	int f1 = 0;
	int f2 = 1;

	int fi = 0;

	if (n == 0)
		return f1;

	if (n == 1)
		return f2;

	int cnt = 1;

	while (cnt < n) {
		fi = (f1 + f2) % 10;
		f1 = f2;
		f2 = fi;

		cnt++;
	}

	return fi;
}

int main() {
	int n;
	std::cin >> n;
	//int c = get_fibonacci_last_digit_naive(n);
	int c = get_fibonacci_last_digit_fast(n);
	std::cout << c << '\n';
}
