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

const int maxn = 105;
int n;
int a[maxn];
int b[500500];
int q[500500];

int naive() {
    vi a(::a, ::a+n);
    sort(all(a));
    set<int> res;
    do {
        int x = a[0];
        fore(i, 1, n-1) {
            x %= a[i];
        }
        res.insert(x);
    } while (next_permutation(all(a)));
    return res.size();
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n;
    forn(i, n) cin >> a[i];
    int lq = 0, rq = 0;
    forn(i, n) forn(j, n) if (i != j && a[i] >= a[j]) {
        int x = a[i] % a[j];
        if (!b[x]) {
//             cout << "init " << x << endl;
            b[x] = 1;
            q[rq++] = x;
        }
    }

    while (lq != rq) {
        int v = q[lq++];
        forn(i, n) {
            int x = v % a[i];
            if (!b[x]) {
//                 cout << x << " from " << v << endl;
                b[x] = 1;
                q[rq++] = x;
            }
        }
    }

    int t = *min_element(a, a+n);
    int res = 0;
    forn(i, t) {
        if (b[i]) {
//             cout << i << " ";
        }
        res += b[i];
    }
//     cout << endl;

    int cnt = count(a, a+n, t);
    if (cnt == 1) {
        ++res;
    }

    cout << res << endl;
//     cout << "naive = " << naive() << endl;
//     assert(res == naive());


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
