#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

std::pair<int, int> partition3(vector<int> &a, vector<int> &b, int l, int r) {
	int x = a[l];
	int dl = abs(b[l] - a[l]);
	int j = l;
	int firstJ = -1, tmpJ;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] < x) {
			j++;
			swap(a[i], a[j]);
			swap(b[i], b[j]);
		}
		else if (a[i] == x) {
			if (dl <= abs(b[i] - a[i])) {
				j++;
				swap(a[i], a[j]);
				swap(b[i], b[j]);
			}
		}
	}
	firstJ = tmpJ = j;
	while (tmpJ >= l && a[tmpJ] == x && a[tmpJ] == dl) {
		firstJ = tmpJ;
		--tmpJ;
	}
	swap(a[l], a[firstJ]);
	swap(b[l], b[firstJ]);
	return std::make_pair(firstJ, j);
}

void randomized_quick_sort2(vector<int> &a, vector<int> &b, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	swap(b[l], b[k]);
	auto&& m = partition3(a, b, l, r);

	randomized_quick_sort2(a, b, l, m.first - 1);
	randomized_quick_sort2(a, b, m.second + 1, r);
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
	vector<int> cnt(points.size());
	randomized_quick_sort2(starts, ends, 0, starts.size() - 1);

	for (int i = 0; i < points.size(); ++i) {
		int l_idx = 0;
		int r_idx = starts.size();
		int last_mid = -1;
		int mid = 0;

		while (l_idx < r_idx) {
			mid = l_idx + (r_idx - l_idx) / 2;
			if (starts[mid] < points[i]) {
				l_idx = mid + 1;
			}
			else {
				r_idx = mid;
			}
		}
		int tmp_l_idx = l_idx - 1;
		// l_idx - нижн€€ граница
		while (l_idx < starts.size() && starts[l_idx] <= points[i] && points[i] <= ends[l_idx]) {
			++cnt[i];
			++l_idx;
		}

		while (tmp_l_idx >= 0) {
			if (starts[tmp_l_idx] <= points[i] && points[i] <= ends[tmp_l_idx]) {
				++cnt[i];
			}
			--tmp_l_idx;
		}
	}

	//write your code here
	return cnt;
}

enum class PointType : int {
	START = 1,
	POINT = 2,
	END = 3	
};

typedef struct Point{
	int value;
	PointType type;
	size_t origin_idx;
};

vector<int> fast_count_segments2(vector<Point>& pts, int m) {
	vector<int> cnt(m);
	int curCnt = 0;

	std::sort(pts.begin(), pts.end(), [](const Point& l, const Point& r) {
		if (l.value < r.value) {
			return true;
		}
		else if (l.value == r.value) {
			return (int)l.type < (int)r.type;
		} 

		return false;
	});

	for (auto&& item : pts) {
		switch (item.type) {
		case PointType::START:
			++curCnt;
			break;
		case PointType::POINT:
			cnt[item.origin_idx] = curCnt;
			break;
		case PointType::END:
			--curCnt;
			break;
		}
	}

	return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
	vector<int> cnt(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	//vector<int> starts(n), ends(n);
	vector<Point> pts(2 * n + m);
	for (size_t i = 0; i < 2 * n; i += 2) {
		//std::cin >> starts[i] >> ends[i];
		std::cin >> pts[i].value >> pts[i + 1].value;
		pts[i].type = PointType::START;
		pts[i + 1].type = PointType::END;
	}
	//vector<int> points(m);
	for (size_t i = 2 * n; i < 2 * n + m; i++) {
		std::cin >> pts[i].value;
		pts[i].type = PointType::POINT;
		pts[i].origin_idx = i - 2 * n;
	}
	//use fast_count_segments
	/*vector<int> cnt = naive_count_segments(starts, ends, points);
	for (size_t i = 0; i < cnt.size(); i++) {
		std::cout << cnt[i] << ' ';
	}

	std::cout << '\n';*/
	vector<int>&& cnt2 = fast_count_segments2(pts, m);
	for (size_t i = 0; i < cnt2.size(); i++) {
		std::cout << cnt2[i] << ' ';
	}

	return 0;
/*
	while (1) {
		int n, m;
		n = rand() % 50000 + 1; // 50000
		m = rand() % 50000 + 1;
		vector<int> starts(n), ends(n);
		for (size_t i = 0; i < starts.size(); i++) {
			//std::cin >> starts[i] >> ends[i];
			starts[i] = rand() % 1000000000 - (2000000000) + 1;
			ends[i] = rand() % 1000000000 - (2000000000) + starts[i];
		}
		vector<int> points(m);
		for (size_t i = 0; i < points.size(); i++) {
			//std::cin >> points[i];
			points[i] = rand() % 1000000000 - (2000000000) + 1;
		}

		vector<int> cnt = naive_count_segments(starts, ends, points);
		vector<int> cnt2 = fast_count_segments(starts, ends, points);
		if (cnt == cnt2) {
			std::cout << "OK!\n";
		}
		else {
			std::cout << "WRONG!\n";
			std::cout << n << ' ' << m << '\n';
			for (int i = 0; i < starts.size(); ++i) {
				std::cout << starts[i] << ' ' << ends[i] << '\n';
			}
			for (int i = 0; i < points.size(); ++i) {
				std::cout << points[i] << ' ';
			}
			break;
		}
	}
	*/
}
