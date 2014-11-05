#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <queue>
#include <set>
#include <map>
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
const int maxn = 46;
i64 f[maxn];
int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("fib.in", "r", stdin);
    freopen("fib.out", "w", stdout);

    f[0] = 1;
    f[1] = 2;
    for (int i = 2; i <= 45; ++i) f[i] = f[i-1] + f[i-2];
    int n, k;
    cin >> n >> k;
    --k;
    while (n) {
        if (f[n-1] > k) {
            printf("0");
            --n;
        } else {
            k -= f[n-1];
            if (n == 1) {
                printf("1");
                break;
            } else {
                printf("10");
                n -= 2;
            }
        }
    }
    printf("\n");

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}