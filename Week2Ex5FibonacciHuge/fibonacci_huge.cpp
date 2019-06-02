#include <iostream>
#include <vector>

//std::vector<long long> pattern;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return current;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    //std::cout << get_fibonacci_huge_naive(n, m) << '\n';

	int status = 0;
	long long value, result, pattern_len = 2;
	//pattern.push_back(0);
	//pattern.push_back(1);

	for (int i = 2; ; ++i) {
		if (status == 2) {
			pattern_len -= 2;
			//pattern.pop_back();
			//pattern.pop_back();
			break;
		}
		value = get_fibonacci_huge_naive(i, m);
		// pattern.push_back(value);
		++pattern_len;
		if (status == 0 && value == 0) {
			++status;
			continue;
		}
		if (status == 1 && value == 1) {
			++status;
			continue;
		}
		status = 0;
	}

	std::cout << get_fibonacci_huge_naive(n % pattern_len, m) << '\n';
}
