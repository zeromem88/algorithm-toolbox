#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

enum class OpType : int {
  Plus1 = 1,
  Mult2 = 2,
  Mult3 = 3,
  NoOp = -1
};

typedef struct Op {
  int val;
  OpType op;
};

void make_optimal(vector<int>& seq, int n) {
  static Op arr[1000000];
  arr[0].val = 0;
  arr[0].op = OpType::NoOp;
  // Single action for
  arr[1].val = arr[2].val = arr[3].val = 1;
  arr[1].op = arr[2].op = arr[3].op = OpType::NoOp;
  seq.push_back(1);

  for(int i = 4; i <= n; ++i) {
    int w1 = 2147483647;
    int w2 = 2147483647;
    int w3 = 2147483647;
    if(i % 3 == 0) {
      // divides by 3
      w1 = arr[i / 3].val + 1;
    }
    if(i % 2 == 0) {
      w2 = arr[i / 2].val + 1;
    }
    w3 = arr[i - 1].val + 1;

    arr[i].val = std::min(std::min(w1, w2), w3);

    if(arr[i].val == w1) {
      arr[i].op = OpType::Mult3;
    } else if(arr[i].val == w2) {
      arr[i].op = OpType::Mult2;
    } else {
      arr[i].op = OpType::Plus1;
    }
  }
  int k = n;
  Op& wi = arr[k];
  while (wi.op != OpType::NoOp) {
	  switch (wi.op) {
	  case OpType::Mult3:
		  k = k / 3;
		  break;
	  case OpType::Mult2:
		  k = k / 2;
		  break;
	  case OpType::Plus1:
		  k = k - 1;
		  break;
	  }
	  wi = arr[k];
	  seq.push_back(k);
  }
  std::reverse(seq.begin() + 1, seq.end());
  if(n > 1) {
    seq.push_back(n);
  }
}

int main() {
  int n;
  vector<int> result;
  std::cin >> n;
  /*vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }*/
  make_optimal(result, n);
  std::cout << result.size() - 1 << std::endl;
  for(auto&& r : result) {
    std::cout << r << " ";
  }
}
