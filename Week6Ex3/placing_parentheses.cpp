#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

long long table_min[15][15];
long long table_max[15][15];

long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}

std::pair<long long, long long> MinAndMax(int i, int j, const string &exp) {
	long long cur_min = std::numeric_limits<long long>::max();
	long long cur_max = std::numeric_limits<long long>::min();
	long long a, b, c, d;
	char op;
	for (int k = i; k < j; ++k) {
		op = exp[k * 2 - 1];
		a = eval(table_max[i][k], table_max[k + 1][j], op);
		b = eval(table_max[i][k], table_min[k + 1][j], op);
		c = eval(table_min[i][k], table_max[k + 1][j], op);
		d = eval(table_min[i][k], table_min[k + 1][j], op);
		cur_min = std::min(a, std::min(b, std::min(c, std::min(d, cur_min))));
		cur_max = std::max(a, std::max(b, std::max(c, std::max(d, cur_max))));
	}

	return std::make_pair(cur_min, cur_max);
}

long long get_maximum_value(const string &exp) {
	int num_of_numbers = (exp.size() + 1) / 2;
	//write your code here
	for (int len = 0, p = 1; len < exp.size(); len += 2, ++p) {
		table_min[p][p] = table_max[p][p] = (exp[len]) - '0';
	}

	for (int s = 1; s <= num_of_numbers; ++s) {
		for (int i = 1; i <= num_of_numbers - s; ++i) {
			int j = i + s;
			auto&& tmp = MinAndMax(i, j, exp);
			table_min[i][j] = tmp.first;
			table_max[i][j] = tmp.second;
		}
	}
	return table_max[1][num_of_numbers];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
}
