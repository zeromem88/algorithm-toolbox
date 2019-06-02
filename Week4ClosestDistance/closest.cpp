#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;

struct Point {
	int x, y;
};

static vector<Point> pts_x;
static vector<Point> pts_y;

static vector<Point> tmp_pts;

static vector<Point> subset;


double minimal_distance(int l, int r) {
	// 1. Already sorted pts_x by x (merge sort)
	double tmp;

	if(l + 3 >= r) {
		double curMin = 100000000000;
		for(int j = l; j < r; ++j) {
			for(int k = j + 1; k < r; ++k) {
				tmp = ((double)pts_x[j].x - (double)pts_x[k].x) * ((double)pts_x[j].x - (double)pts_x[k].x) +
					((double)pts_x[j].y - (double)pts_x[k].y) * ((double)pts_x[j].y - (double)pts_x[k].y);
				curMin = std::min(curMin, tmp);
			}
		}
		return curMin;
	}
	
	// 2. Calculate left min and right min distances
	int mid = r - (r - l) / 2;

	double min_left = minimal_distance(l, mid);
	double min_right = minimal_distance(mid, r);
	double cur_iter_min = std::min(min_left, min_right);

	// Now we have sorted and merged our left&right halves
	// Calculate coordinate of middle vertical line
	//double vert_x = ((double)tmp_pts[r - 1].x - (double)tmp_pts[l].x) / 2 + (double)tmp_pts[l].x;
	double vert_x = pts_x[mid].x;
	
	int subset_idx = 0;

	for (size_t i = l; i < r; ++i) {
		if (abs((double)pts_x[i].x - vert_x) <= cur_iter_min) {
			// Filter out points within cur_iter_min
			subset[subset_idx++] = pts_x[i];
		}
	}

	// TODO: ???
	std::sort(subset.begin(), subset.begin() + subset_idx, [](const Point& l, const Point& r) {
		if (l.y < r.y) // First by y
			return true;

		return false;
	});

	double result = cur_iter_min;
	
	for (size_t j = 0; j < subset_idx; ++j) {
		for (size_t k = j + 1; k < subset_idx && k < j + 7; ++k) {
			// Check only max for 7 elements
			tmp = ((double)subset[j].x - (double)subset[k].x) * ((double)subset[j].x - (double)subset[k].x) +
				((double)subset[j].y - (double)subset[k].y) * ((double)subset[j].y - (double)subset[k].y);
			result = std::min(result, tmp);
		}
	}

	return result;
}

double minimal_distance_sort(int l, int r) {
	//write your code here
	double result = 100000000000;
	double tmp;

	if (l + 2 == r) {
		if (pts_x[l + 1].x < pts_x[l].x) {
			std::swap(pts_x[l + 1], pts_x[l]);
		}
		return result;
	}
	else if (l + 1 == r) {
		return result; 
	}
	// Tail recursion optimization???
	int mid = r - (r - l) / 2;

	minimal_distance_sort(l, mid);
	minimal_distance_sort(mid, r);

	int lk = l;
	int rk = mid;
	
	for (size_t k = l; k < r; ++k) {
		if (lk < mid && rk < r) {
			if (pts_x[lk].x <= pts_x[rk].x) {
				tmp_pts[k] = pts_x[lk];
				++lk;
			}
			else {
				tmp_pts[k] = pts_x[rk];
				++rk;
			}
		}
		else if (lk < mid) {
			tmp_pts[k] = pts_x[lk];
			++lk;
		}
		else {
			tmp_pts[k] = pts_x[rk];
			++rk;
		}
	}

	for (size_t i = l; i < r; ++i) {
		pts_x[i] = tmp_pts[i];
	}

	return result;
}

double minimal_distance_naive() {
	double result = 100000000000, tmp;

	for (size_t j = 0; j < pts_x.size(); ++j) {
		for (size_t k = j + 1; k < pts_x.size(); ++k) {
			tmp = ((double)pts_x[j].x - (double)pts_x[k].x) * ((double)pts_x[j].x - (double)pts_x[k].x) +
				((double)pts_x[j].y - (double)pts_x[k].y) * ((double)pts_x[j].y - (double)pts_x[k].y);
			result = std::min(result, tmp);
		}
	}

	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	pts_x.resize(n);
	//pts_y.resize(n);
	tmp_pts.resize(n);
	subset.resize(n);

	for (size_t i = 0; i < n; i++) {
		std::cin >> pts_x[i].x >> pts_x[i].y;
		//pts_y[i] = pts_x[i];
	}
	
	
	//std::cout << std::setprecision(9) << sqrt(minimal_distance_naive()) << "\n";

	//std::sort(pts_x.begin(), pts_x.end(), [](const Point &a, const Point &b) { return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });
	minimal_distance_sort(0, n);
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << sqrt(minimal_distance(0, n)) << "\n";
	return 0;
	
	/*
	while (1) {
		size_t n = rand() % 10000 + 2;
		pts_x.resize(n);
		
		tmp_pts.resize(n);
		subset.resize(n);
		for (size_t i = 0; i < n; ++i) {
			pts_x[i].x = rand() % 1000000000 - (2000000000) + 1; // rand() % 1000000000 - (2000000000) + 1;
			pts_x[i].y = rand() % 1000000000 - (2000000000) + 1; // rand() % 1000000000 - (2000000000) + 1;
		}

		pts_y = pts_x;

		double naive = sqrt(minimal_distance_naive());
		minimal_distance_sort(0, n);
		double fast = sqrt(minimal_distance(0, n));

		if (abs(naive - fast) >= 0.001) {
			std::cout << "ERROR!" << "\n";
			std::cout << n << "\n";
			for (size_t i = 0; i < n; ++i) {
				std::cout << pts_y[i].x << ' ' << pts_y[i].y << "\n";
			}
			std::cout << "\n";
			break;
		}
		else {
			std::cout << "OK!";
		}
	}

	*/
}

/*
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <math.h>

#define __DBL_MAX std::numeric_limits<double>::max()

struct Point
{
	int x, y;

	double dist(const Point &b) const
	{
		return sqrt((x - b.x)*(x - b.x) +
			(y - b.y)*(y - b.y));
	}
};

typedef std::vector<Point> Points;

double closestDist(const Points &v, double min = __DBL_MAX)
{
	for (auto it1 = v.begin(); it1 != v.end(); ++it1)
		for (auto it2 = it1 + 1; it2 != v.end() && abs(it2->y - it1->y) < min; ++it2)
			min = std::min(it1->dist(*it2), min);

	return min;
}

double closestDivAndConq(const Points &v)
{
	if (v.size() <= 3)
		return closestDist(v);

	size_t mid = v.size() / 2;

	Points Pl(v.begin(), v.begin() + mid);
	Points Pr(v.begin() + mid, v.end());

	double dl = closestDivAndConq(Pl);
	double dr = closestDivAndConq(Pr);

	double d = std::min(dl, dr);

	Points strip;

	const Point &midPoint = v[mid];

	for (auto p : v)
		if (abs(midPoint.x - p.x) < d)
			strip.push_back(p);

	std::sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) { return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); });

	return std::min(d, closestDist(strip, d));
}

double closest(Points &v)
{
	std::sort(v.begin(), v.end(), [](const Point &a, const Point &b) { return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });

	return closestDivAndConq(v);
}

int main()
{
	Points v({ { 9,10 },
	{ 8 ,3 },
	{ 3 ,9 },
	{ 3 ,9 },
	{ 10,1 },
	{ 8 ,9 },
	{ 2 ,6 },
	{ 9 ,7 },
	{ 2 ,3 },
	{ 5 ,3 },
	{ 6 ,9 } });

	double ret = closest(v);
	if (ret == __DBL_MAX)
		return -1;

	std::cout << std::setprecision(std::numeric_limits<double>::digits10) << ret << std::endl;

	return 0;
}*/