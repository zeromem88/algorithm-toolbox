#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;

typedef std::pair<int, int> VecPair;

double get_optimal_value(int capacity, vector<VecPair> data) {
	double value = 0.0;
	int cur_capacity = capacity;

	// данные отсортированы, выбираем в порядке следования
	for (size_t i = 0; cur_capacity > 0 && i < data.size(); ++i) {
		if (cur_capacity >= data[i].second) {
			value += data[i].first;
		}
		else {
			value += data[i].first * ((double)cur_capacity / (double)data[i].second);
		}
		cur_capacity -= data[i].second;
	}

	return value;
}

double get_optimal_value_slow(int capacity, vector<VecPair> data) {
	double value = 0.0;
	int cur_capacity = capacity;

	for (size_t i = 0; i < data.size(); ++i) {
		int cur_max_idx = 0;
		double cur_max = 0;

		if (cur_capacity == 0)
			return value;

		// ищем макс vi/wi
		for (size_t j = 0; j < data.size(); ++j) {
			if (data[j].second > 0) {
				double q = (double)data[j].first / (double)data[j].second;
				if (cur_max < q) {
					cur_max_idx = j;
					cur_max = q;
				}
			}
		}
		int a = std::min(cur_capacity, data[cur_max_idx].second);
		value += data[cur_max_idx].first * ((double) a / (double)data[cur_max_idx].second);

		cur_capacity -= a;
		data[cur_max_idx].second = 0;
	}

	return value;
}

int main() {
	int n;
	int capacity;
	std::cin >> n >> capacity;
	vector<VecPair> data(n);

	for (int i = 0; i < n; i++) {
		VecPair& p = data[i];
		std::cin >> p.first >> p.second;
	}

	/*while (1) {
		n = rand() % 1000 + 1;
		capacity = rand() % 200000;

		vector<VecPair> data;

		for (int i = 0; i < n; ++i) {
			int v = rand() % 200000;
			int w = rand() % 200000 + 1;
			data.push_back(std::make_pair(v, w));
		}

		double optimal_value_slow = get_optimal_value_slow(capacity, data);*/

		// сортировка по-убыванию
		std::sort(data.begin(), data.end(), [](const VecPair& left, const VecPair& right) {
			double l = (double)left.first / (double)left.second;
			double r = (double)right.first / (double)right.second;
			return l > r;
		});

		double optimal_value = get_optimal_value(capacity, data);

		std::cout.precision(10);
	//	std::cout << optimal_value_slow << std::endl;
		std::cout << optimal_value << std::endl;

	/*	if (fabs(optimal_value_slow - optimal_value) >= 0.0001) {
			std::cout << "ERROR!";
			std::cin >> n;
			break;
		}
		else {
			std::cout << "OK!";
		}
	}*/

	return 0;
}
