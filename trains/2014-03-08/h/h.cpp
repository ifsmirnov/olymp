#include <iostream>
#include <cstdio>
#include <cmath>
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
typedef double ld;
const int inf = 1e9+100500;

ld d(pii a, pii b) {
    return sqrt(1.0 * (a.first - b.first) * (a.first - b.first) + 1.0 * (a.second - b.second) * (a.second - b.second));
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    cout << fixed;
    cout.precision(2);
    while (N > 0) {
        vector<pii> a(N);
        forn(i, N) {
            cin >> a[i].second >> a[i].first;
        }
        sort(all(a));
        vector<ld> ans(N + 1, 1e9);
        ans[0] = ans[1] = 0.0;
        for (int i = 1; i < N; ++i) {
            double closest = 1e9;
            forn(j, i) {
                closest = min(closest, d(a[j], a[i]));
                if (a[j + 1].first == a[i].first) {
                    ans[i + 1] = min(ans[i + 1], ans[j + 1] + closest + a[i].second - a[j + 1].second);
                }
            }
        }
        
        cout << ans[N] << '\n';
        cin >> N;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
