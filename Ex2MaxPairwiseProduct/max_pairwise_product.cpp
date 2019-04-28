#include <iostream>
#include <vector>
#include <algorithm>

int MaxPairwiseProduct(const std::vector<int>& numbers) {
    int max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    }

    return max_product;
}

long long MaxPairwiseProductFast(const std::vector<int>& numbers) {
	int max_id1 = 0, max_id2 = -1;
	int inpSize = numbers.size();

	for (int i = 1; i < inpSize; ++i) {
		if (numbers[i] > numbers[max_id1]) {
			max_id1 = i;
		}
	}

	for (int i = 0; i < inpSize; ++i) {
		if (i != max_id1 && (max_id2 == -1 || numbers[i] > numbers[max_id2])) {
			max_id2 = i;
		}
	}

	return (long long)numbers[max_id1] * (long long)numbers[max_id2];
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << MaxPairwiseProductFast(numbers) << "\n";
    return 0;
}
