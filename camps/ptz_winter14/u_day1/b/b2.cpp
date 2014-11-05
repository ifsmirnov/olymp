#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
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
const int maxn = 100500;

const int maxx = 10;

int ans[11][11];

void rec(int x, int sum, int op, int k, int fact) {
    if (sum >= x * fact) {
        return;
    }
    ans[x][sum / fact] = min(ans[x][sum/fact], op);
    if (k > x) {
        return;
    }
    for (int i = 0; i < k; ++i) {
        rec(x, sum + i * fact * x / k, op + i, k + 1, fact);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    for (int i = 1; i <= 10; ++i) {
        for (int j = 0; j <= 10; ++j) {
            ans[i][j] = 10000;
        }
    }
    int fact = 1;
    for (int i = 1; i <= 10; ++i) {
        fact *= i;
        rec(i, 0, 0, 2, fact);
        /*for (int j = 0; j < i; ++j) {
            cerr << i << ' ' << j << ' ' << ans[i][j] << '\n';
        }*/
    }
    int x, y;
    while (scanf("%d%d", &x, &y) > 0) {
        if (y < x) {
            //printf("-1\n");
            cout << -1 << '\n';
        } else {
            cout << x - 1 + (y / x) - 1 + ans[x][y % x] << '\n';
        }
    }
    //while (solve());
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
