#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
	int start, end;
	bool operator == (const Segment& l) const {
		if (start == l.start && end == l.end)
			return true;

		return false;
	};
};

vector<int> optimal_points_slow(vector<Segment> segments) {
	vector<int> points;

	vector<Segment> intersected;
	vector<Segment> copy_segments(segments);
	int curPoint = -1;

	while (!segments.empty()) {
		for (size_t i = 0; i < segments.size(); ++i) {
			bool hasIntersections = true;
			for (size_t j = 0; j < intersected.size(); ++j) {
				if (segments[i].start > intersected[j].end) {
					hasIntersections = false;
					break;
				}
				if (segments[i].end < intersected[j].start) {
					hasIntersections = false;
					break;
				}
				if (curPoint == -1) {
					curPoint = intersected[j].end;
				}
				else {
					curPoint = std::min(intersected[j].end, curPoint);
				}
			}
			if (hasIntersections) {
				intersected.push_back(segments[i]);
				auto it = std::find(copy_segments.begin(), copy_segments.end(), segments[i]);
				copy_segments.erase(it);
				curPoint = std::min(segments[i].end, curPoint);
			}
		}
		if (curPoint == -1) {
			points.push_back(intersected[0].end);
		}
		else {
			points.push_back(curPoint);
		}
		curPoint = -1;
		segments = copy_segments;
		intersected.clear();
	}

	return points;
}

vector<int> optimal_points_(vector<Segment> &segments) {
	vector<int> points;

	Segment curSegment = { -1, 2147483647 };

	std::sort(segments.begin(), segments.end(), [](const Segment& l, const Segment& r) {
		return l.end < r.end;
	});

	//write your code here
	for (size_t i = 0; i < segments.size(); ++i) {
		if (segments[i].start > curSegment.end) {
			points.push_back(curSegment.end);
			curSegment.start = -1;
			curSegment.end = 2147483647;
		}
		curSegment.start = std::max(segments[i].start, curSegment.start);
		curSegment.end = std::min(segments[i].end, curSegment.end);
	}

	points.push_back(curSegment.end);
	return points;
}

vector<int> optimal_points(vector<Segment> segments) {
	vector<int> points;

	while (segments.size() > 0) {
		int min_right = 2147483647;
		for (int i = 0; i < segments.size(); ++i) {
			min_right = std::min(min_right, segments[i].end);
		}
		points.push_back(min_right);
		auto it = segments.begin();

		while (it != segments.end()) {
			if (it->start <= min_right && min_right <= it->end) {
				it = segments.erase(it);
			}
			else {
				++it;
			}
		}

	}

	return points;
}

int main() {
	int n = 0;
	std::cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
		std::cin >> segments[i].start >> segments[i].end;
	}
	/*while (1) {
		segments.clear();
		n = rand() % 100 + 1;

		for (int i = 0; i < n; ++i) {
			int v = rand() % 100000000;
			int w = rand() % (100000000 - v) + v;
			segments.push_back(Segment{ v, w });
		}*/

		vector<int> points_fast = optimal_points_(segments);
		std::cout << points_fast.size() << "\n";
		for (size_t i = 0; i < points_fast.size(); ++i) {
			std::cout << points_fast[i] << " ";
		}

/*		vector<int> points = optimal_points_(segments);
		std::cout << "\n===============================\n";
		std::cout << points.size() << "\n";
		for (size_t i = 0; i < points.size(); ++i) {
			std::cout << points[i] << " ";
		}
		std::cout << "\n===============================\n";
		std::cout << points_fast.size() << "\n";
		for (size_t i = 0; i < points_fast.size(); ++i) {
			std::cout << points_fast[i] << " ";
		}
		std::cout << "\n===============================\n";
		if (points_fast.size() != points.size()) {
			std::cout << "ERROR! Different sizes!";
			break;
		}
		std::sort(points.begin(), points.end());
		std::sort(points_fast.begin(), points_fast.end());

		if (points != points_fast) {
			std::cout << "ERROR! Different content!";
			break;
		}
		std::cout << "OK!";
	}*/
}
