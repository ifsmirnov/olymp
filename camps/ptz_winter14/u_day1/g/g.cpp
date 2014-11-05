#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <cmath>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long i64;
typedef unsigned long long u64;
const int inf = 1e9+100500;
const int maxn = 200500;

long double T[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    T[0] = 0.5 * atan2l(0.0, -1.0);
    T[1] = 1.0;
    for (int i = 2; i < maxn; ++i) {
        T[i] = T[i - 2] * (i - 1) / i;
    }
    
    int N, R;
    while (scanf("%d%d", &N, &R) > 0) {
        printf("%.10lf\n", (double)(1.0 * R / (N + 1) / T[N]));
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
