#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

typedef struct Vals{
	int val;
	bool taken;
};

Vals value[10001][301];

int optimal_weight(int W, const vector<int> &w) {

	int weight = 0;

	for (int i = 0; i <= W; ++i) {
		value[i][0].val = 0;
		value[i][0].taken = false;
	}

	for (int k = 0; k <= w.size(); ++k) {
		value[0][k].val = 0;
		value[0][k].taken = false;
	}

	for (int i = 1; i <= w.size(); ++i) {
		for (int k = 1; k <= W; ++k) {
			value[k][i].val = value[k][i - 1].val;
			value[k][i].taken = false;
			if (w[i - 1] <= k) {
				int tmp = value[k - w[i - 1]][i - 1].val + w[i - 1];
				if (value[k][i].val < tmp) {
					value[k][i].val = tmp;
					value[k][i].taken = true;
				}
			}
		}
	}

	/*printf("     ");
	for (int i = 0; i <= W; ++i) {
		printf("%d ", i);
	}
	for (int i = 0; i <= w.size(); ++i) {
		printf("\n %d - ", i);
		for (int k = 0; k <= W; ++k) {
			printf("%d ", value[k][i].val);
		}
	}*/

	int i = W, j = w.size();

	while (i > 0 && j > 0) {
		if (value[i][j].taken) {
			weight += w[j - 1];
			i -= w[j - 1];
		}
		j--;
	}

	return weight;
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';
}
