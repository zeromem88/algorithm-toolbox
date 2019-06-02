#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
	long long number_of_inversions = 0;
	if (right <= left + 1) {
		b[left] = a[left];
		return number_of_inversions;
	}
	size_t ave = left + (right - left) / 2;
	number_of_inversions += get_number_of_inversions(a, b, left, ave);
	number_of_inversions += get_number_of_inversions(a, b, ave, right);
	//write your code here
	int i = left;
	int j = left, k = ave;
	while (i < right) {
		int bj = 0;
		int ck = 0;

		if (k >= right) {
			ck = 2147483647;
		}
		else {
			ck = a[k];
		}

		if (j >= ave) {
			bj = 2147483647;
		}
		else {
			bj = a[j];
		}

		if (bj <= ck) {
			b[i] = bj;
			++j;
		}
		else {
			b[i] = ck;
			++k;
			int tmpJ = j;
			while (tmpJ < ave) {
				if (a[tmpJ] > ck) {
					++number_of_inversions;
				}
				++tmpJ;
			}
		}
		++i;
	}
	for (int i = left; i < right; ++i) {
		a[i] = b[i];
	}
	return number_of_inversions;
}

long long inv_naive(const vector<int>& a) {
	long long result = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = i + 1; j < a.size(); j++) {
			if (a[i] > a[j]) {
				++result;
			}
		}
	}
	return result;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	vector<int> b(a.size());
	std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
	//std::cout << "OK!";
	return 0;
	
	/*
	while (1) {
		int n = rand() % 10000 + 1;
		//std::cin >> n;
		vector<int> a(n), b(n);
		for (size_t i = 0; i < a.size(); ++i) {
			//std::cin >> a[i];
			b[i] = a[i] = rand() % 100000000;
		}
		long long r1, r2;
		r1 = inv_naive(a);
		r2 = get_number_of_inversions(a, b, 0, a.size());
		std::cout << r1 << '\n';
		std::cout << r2 << '\n';

		if (r1 == r2) {
			std::cout << "OK" << '\n';
		} else{
			std::cout << "WRONG!" << '\n';
			for (auto&& v : b) {
				std::cout << v << ' ';
			}
			std::cout << '\n';
			break;
		}
	}*/
}
