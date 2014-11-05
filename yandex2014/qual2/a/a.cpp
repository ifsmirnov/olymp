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

int n, k;
int c[100500];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> k;
    forn(i, n) cin >> c[i];

    i64 res = 1;
    forn(i, n) {
        res += max(0, (c[i] - 2 * (k - 1) + k - 1) / k);
    }

//     cout << "res if 0=1 = " << res << endl;

    i64 r1 = 0;
    int cadd = 0;
    forn(i, n) {
        int x = max(0, (c[i] + 2 - 2 * ((k+1)/2) + k - 1) / k);
        int y = max(0, (c[i] + 3 - 2 * ((k+1)/2) + k - 1) / k);
//         cout << "x = " << x << ", y = " << y << endl;
        r1 += x;
        if (k%2 == 1 && x != y) {
            cadd = 1;
        }
    }

    res = max(res, r1 + cadd);

    cout << res << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
