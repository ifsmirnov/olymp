#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
#include <cassert>

using namespace std;

const int BITS = 17;
const int MAX = (1 << BITS) - 1;

int kb[1 << BITS];

const int N = (1 << 21) + 10;

long long bad[N];
double f[N];
char word[777][777];

int main() {
    freopen("input.txt", "r", stdin);
//   int cnt;
//   scanf("%d", &cnt);
//   for (int i = 0; i < cnt; i++) {
//     scanf("%s", word[i]);
//   }
    int cnt = 50;
    int n = 20;
    for (int i = 0; i < cnt; ++i) for (int j = 0; j < n; ++j)  word[i][j] = rand()%2+'a';
//   int n = strlen(word[0]);
  for (int t = 0; t < (1 << n); t++) {
    bad[t] = 0;
  }
  for (int i = 0; i < cnt; i++) {
    for (int j = i + 1; j < cnt; j++) {
      int diff = 0;
      for (int k = 0; k < n; k++) {
        if (word[i][k] == word[j][k]) {
          diff |= (1 << k);
        }
      }
      bad[diff] |= (1LL << i);
      bad[diff] |= (1LL << j);
    }
  }
  kb[0] = 0;
  for (int i = 1; i < (1 << BITS); i++) {
    kb[i] = kb[i & (i - 1)] + 1;
  }
  for (int t = (1 << n) - 1; t >= 0; t--) {
    for (int i = 0; i < n; i++) {
      if (t & (1 << i)) {
        bad[t ^ (1 << i)] |= bad[t];
      }
    }
    int p = 0;
    f[t] = 0.0;
    for (int i = 0; i < n; i++) {
      if (!(t & (1 << i))) {
        f[t] += f[t ^ (1 << i)];
        p++;
      }
    }
    if (p > 0) {
      f[t] /= p;
    }
    f[t] += (kb[bad[t] & MAX] + kb[(bad[t] >> BITS) & MAX] + kb[(bad[t] >> (2 * BITS))]) * 1.0 / cnt;
  }
  printf("%.17lf\n", f[0]);
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
  return 0;
}
