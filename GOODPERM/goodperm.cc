#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;
int main()
{
  int T(0); // number of tests
  cin >> T;
  for (;T>0;--T) {
    // read N,K
    int N(0);
    int K(0);
    cin >> N >> K;

    // read A
    vector<int> A; A.reserve(N);
    copy_n(istream_iterator<int>(cin), N, back_inserter(A));

    // find the missing numbers
    vector<int> missing_numbers(N+1,0);
    iota(missing_numbers.begin(), missing_numbers.end(), 0);
    vector<int> hole_pos;
    for (auto i=0; i<N; ++i) {
      auto a = A[i];
      if (a == 0) {
        hole_pos.push_back(i);
      } else {
        missing_numbers[a] = 0;
      }
    }

    string missing;
    copy_if(missing_numbers.begin(), missing_numbers.end(), back_inserter(missing), [] (int n) {return n >0;});

    int good_perm(0);
    // generate permutations
    do {
      // copy missing permutation to holes
      auto hole_pos_it(hole_pos.begin());
      for_each(missing.begin(), missing.end(), [&A, &hole_pos_it] (char c) {
          A[*hole_pos_it] = c;
          ++hole_pos_it;
        });

      // check if it is a good permutation
      vector<int> diffs;
      adjacent_difference(A.begin(), A.end(), back_inserter(diffs));
      if (K == count_if(next(diffs.begin()), diffs.end(), [] (int d) { return d>0; }) ) {
        ++good_perm;
      }
    } while( next_permutation(missing.begin(), missing.end()));

    // prinr number of good permutations
    cout << good_perm << "\n";

  }  

}
