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

int dp[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int N;
    double M;
    while (true) {
        cin >> N >> M;
        if (N == 0) break;
        int P = (int)(100 * M + 0.5);
        forn(i, P + 1) dp[i] = -1e9;
        dp[0] = 0;
        forn(i, N) {
            int x;
            double m;
            cin >> x >> m;
            int p = (int)(100 * m + 0.5);
            for (int j = p; j <= P; ++j) {
                if (dp[j - p] >= 0) {
                    dp[j] = max(dp[j], dp[j - p] + x);
                }
            }
        }
        cout << *max_element(dp, dp + P + 1) << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
