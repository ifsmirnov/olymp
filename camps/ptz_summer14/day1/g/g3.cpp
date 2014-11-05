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
const int maxn = 300500;

int n, k;
int a[maxn], b[maxn];
void cycle() {
    vector<vi> res;
    forn(i, n) b[i] = 0;
    ford(i, n) if (b[i] == 0) {
        vi t;
        for (int j = i; !b[j]; j = a[j]) {
            t.pb(j);
            b[j] = 1;
        }
        res.pb(t);
    }
    auto cmp = [](const vi& a, const vi& b) { return a[0] < b[0]; };
    sort(all(res), cmp);
    int k = 0;
    forn(i, res.size()) forn(j, res[i].size()) b[k++] = res[i][j];
    printf("%d r", n);
    forn(i, n) printf(" %d", b[i] + 1);
    printf("\n");
}

void record() {
    int mx = a[0], i = 0;
    while (i != n) {
        if (i == n-1 || a[i+1] > mx) {
            b[a[i]] = mx;
            mx = a[i+1];
        } else {
            b[a[i]] = a[i+1];
        }
        ++i;
    }
    printf("%d c", n);
    forn(i, n) printf(" %d", b[i] + 1);
    printf("\n");
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("records-and-cycles.in", "r", stdin);
    freopen("records-and-cycles.out", "w", stdout);

    int q;
    scanf("%d", &q);
    printf("%d\n", q);
    forn(i, q) {
        char t[3];
        scanf("%d%s", &n, t);
        forn(i, n) scanf("%d", &a[i]), --a[i];
        if (t[0] == 'c') cycle();
        else record();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
