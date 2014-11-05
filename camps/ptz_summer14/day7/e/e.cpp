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
const int maxn = 1000500;

int n;
int a[maxn], b[maxn];
multiset<int> f;
int k;
i64 add;

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%d%d", &n, &k);
    i64 s = 0;
    forn(i, n) scanf("%d", &b[i]), s += b[i];
    forn(i, n) scanf("%d", &a[i]);
    sort(a, a+n);
    f.insert(b, b+n);

    ford(i, n) {
        auto it = f.lower_bound(a[i]);
        if (it == f.end()) {
            if (k == 0) {
                printf("NIE\n");
                return 0;
            }
            add += a[i];
            --k;
            a[i] = 0;
        } else {
            a[i] = *it - a[i];
            f.erase(it);
        }
    }
    for (auto t: f) add -= t;
    sort(a, a+n, greater<int>());
    forn(i, k) add -= a[i];
    cout << s+add << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
