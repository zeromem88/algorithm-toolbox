#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
	int stops_cnt = 0;
	int cur_stop = 0;
	bool isFirst = true;

	for (int i = 0; i < stops.size() - 1;++i) {
		if(stops[i + 1] - stops[i] > tank)

		if (stops[i + 1] - cur_stop > tank) {
			cur_stop = stops[i];
			++stops_cnt;
			isFirst = true;
		}
		isFirst = false;
	}

    return stops_cnt;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
