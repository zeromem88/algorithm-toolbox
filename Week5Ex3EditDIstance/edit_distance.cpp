#include <iostream>
#include <string>
#include <algorithm>

using std::string;

enum class Dir : int {
	Left = 1,
	Diag = 2,
	Top = 3,
	NoOp = 100
};

typedef struct Item {
	int val;
	Dir dir;
};

static Item T[101][101];

int edit_distance(const string &str1, const string &str2) {
	size_t s1, s2;
	s1 = str1.size();
	s2 = str2.size();
	for (int i = 0; i <= s1; ++i) {
		T[i][0].val = i;
		T[i][0].dir = Dir::NoOp;
	}
	for (int j = 1; j <= s2; ++j) {
		T[0][j].val = j;
		T[0][j].dir = Dir::NoOp;
	}

	for (int j = 1; j <= s2; ++j) {
		for (int i = 1; i <= s1; ++i) {
			int ins = T[i][j - 1].val + 1;
			int dels = T[i - 1][j].val + 1;
			int match = T[i - 1][j - 1].val;
			int mismatch = T[i - 1][j - 1].val + 1;
			if (str1[i - 1] == str2[j - 1]) {
				// T[i][j] = std::min(std::min(ins, dels), match);
				if (ins < dels) {
					if (ins < match) {
						// ins
						T[i][j].val = ins;
						T[i][j].dir = Dir::Top;
					}
					else {
						// match
						T[i][j].val = match;
						T[i][j].dir = Dir::Diag;
					}
				}
				else {
					if (dels < match) {
						// dels
						T[i][j].val = dels;
						T[i][j].dir = Dir::Left;
					}
					else {
						// match
						T[i][j].val = match;
						T[i][j].dir = Dir::Diag;
					}
				}
			}
			else {
				//T[i][j] = std::min(std::min(ins, dels), mismatch);
				if (ins < dels) {
					if (ins < mismatch) {
						// ins
						T[i][j].val = ins;
						T[i][j].dir = Dir::Top;
					}
					else {
						// match
						T[i][j].val = mismatch;
						T[i][j].dir = Dir::Diag;
					}
				}
				else {
					if (dels < mismatch) {
						// dels
						T[i][j].val = dels;
						T[i][j].dir = Dir::Left;
					}
					else {
						// match
						T[i][j].val = mismatch;
						T[i][j].dir = Dir::Diag;
					}
				}
			}
		}
	}

	return T[s1][s2].val;
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
