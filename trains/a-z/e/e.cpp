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
const int maxn = 100;

int res[maxn], k;
void go(int n, int p) {
    if (n == 0) {
        forn(i, k-1) printf("%d+", res[i]);
        printf("%d\n", res[k-1]);
        return;
    }
    for (int x = min(p, n); x >= 1; --x) {
        res[k++] = x;
        go(n-x, x);
        --k;
    }
}

int main() {
#ifdef HOME
#endif
    freopen("part.in", "r", stdin);
    freopen("part.out", "w", stdout);

    int n;
    cin >> n;
    go(n, n);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
