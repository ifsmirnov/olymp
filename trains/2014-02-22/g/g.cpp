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
const int maxn = 100;

int n;
int l[maxn], r[maxn];
int a[maxn];
int b[maxn];

bool check() {
    set<int> t;
    forn(i, n) {
        forn(j, i) {
            assert(a[j] <= a[i]);
            assert(!t.count(a[i] - a[j]));
            t.insert(a[j] - a[i]);
        }
    }
    return true;
}

// void out() {
//     forn(i, n) cout << a[i] << " "; cout << endl;
// }

int res = 0;
void go(int k) {
    if (k == n) {
        ++res;
        return;
    }
    int lft = max(l[k], a[k-1] + 1);
    fore(p, lft, r[k]) {
        bool ok = true;
        forn(i, k) {
            if (b[p - a[i]]) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        forn(i, k) {
            b[p - a[i]]++;
        }
        a[k] = p;
        go(k+1);
        forn(i, k) {
            b[p - a[i]]--;
        }
    }
}

void scan() {
    scanf("%d", &n);
    forn(i, n-1) scanf("%d%d", &l[i+1], &r[i+1]);
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("palantir.in", "r", stdin);
    freopen("palantir.out", "w", stdout);

    scan();
    if (n == 2) {
        cout << r[1] - l[1] + 1 << endl;
    } else {
        go(1);
        cout << res << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
