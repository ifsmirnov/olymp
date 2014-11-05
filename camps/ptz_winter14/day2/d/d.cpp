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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    i64 N, K;
    cin >> N >> K;
    if (K == 1) cout << N * (N + 1) / 2 << '\n';
    else {
        double ans = 0, p = 1;
        for (int i = 1; i < 2000 && i <= N; ++i) {
            ans += (N - i + 1) * p;
            if (i % 2 == 1) {
                p /= K;
            }
        }
        cout.precision(10);
        cout << fixed;
        cout << ans << '\n';
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
