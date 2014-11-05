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
const int maxn = 105;

int n;
vi a[maxn];
int s1[maxn], s2[maxn];

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        int k;
        scanf("%d", &k);
        a[i].resize(k);
        forn(j, k) scanf("%d", &a[i][j]);
    }
}

void solve() {
    forn(i, n) {
        {
            int s = 0;
            int l = 0, r = a[i].size() - 1;
            int st = 1;
            while (l <= r) {
                if (st) s += a[i][l++];
                else s -= a[i][r--];
                st = !st;
            }
            s1[i] = s;
        }
        {
            int s = 0;
            int l = 0, r = a[i].size() - 1;
            int st = 0;
            while (l <= r) {
                if (st) s += a[i][l++];
                else s -= a[i][r--];
                st = !st;
            }
            s2[i] = s;
        }
    }
    i64 totals = 0;
    forn(i, n) forn(j, a[i].size()) totals += a[i][j];

//     forn(i, n) {
//         cout << s1[i] << " " << s2[i] << endl;
//     }
//     cout << endl;

    int s = 0;
    int st = 0;
    forn(i, n) {
        if (st == 0) {
//             cout << "st = 0 " << endl;
            int p = max_element(s1, s1+n) - s1;
//             cout << "sel " << p << endl;
            s += s1[p];
            s1[p] = -1000000000;
            s2[p] = 1000000000;
            st ^= (a[p].size() % 2);
        } else {
//             cout << "st = 1" << endl;
            int p = min_element(s2, s2+n) - s2;
//             cout << "sel " << p << endl;
            s += s2[p];
            s1[p] = -1000000000;
            s2[p] = 1000000000;
            st ^= (a[p].size() % 2);
        }
    }
//     cout << "s = " << s << endl;
    cout << (totals + s) / 2 << " " << (totals - s) / 2 << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
