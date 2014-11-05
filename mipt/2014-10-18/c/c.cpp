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
const int maxn = 100500;

const int sz = 1<<17;

struct node {
    node() : k(0) {
        forn(i, 4) a[i] = 0;
    }
    i64 a[4];
    int k;
    void merge(const node& x, const node& y) {
//         forn(i, x.k) cout << x.a[i] << " ";
//         cout << "| ";
//         forn(i, y.k) cout << y.a[i] << " ";
//         cout << " --> ";
        k = 0;
        forn(i, x.k) {
            a[k++] = x.a[i];
        }
        forn(i, y.k) {
            a[k++] = y.a[i];
        }
        while (true) {
            bool done = false;
            forn(i, k) {
                if (!a[i]) {
                    for (int j = i; j < k-1; ++j) {
                        a[j] = a[j+1];
                    }
                    --k;
                    done = true;
                    break;
                }
            }
            if (!done) {
                forn(i, k-1) {
                    if (!(a[i] < 0 && a[i+1] > 0)) {
                        a[i] += a[i+1];
                        for (int j = i+1; j < k-1; ++j) {
                            a[j] = a[j+1];
                        }
                        --k;
                        done = true;
                        break;
                    }
                }
            }
            if (!done) break;
        }
//         forn(i, k) cout << a[i] << " "; cout << endl;
        assert(k <= 2);
    }
} a[sz * 2];

i64 add(int i, i64 x) {
    i += sz;
    if (a[i].k == 0) {
        a[i].k = 1;
        a[i].a[0] = 0;
    }
    a[i].a[0] += x;
    for (i /= 2; i; i /= 2) {
        a[i].merge(a[i*2], a[i*2+1]);
    }
    if (a[1].k == 0) {
        return 0;
    } else {
        return min(0ll, a[1].a[0]);
    }
}

i64 get_date(string s1, string s2) {
    i64 res = 0;
    int d, m;
    sscanf(s1.c_str(), "%d.%d", &d, &m);
    res = m*100 + d;
    int h;
    sscanf(s2.c_str(), "%d:%d", &h, &m);
    res = res * 10000 + h * 100 + m;
    return res;
}

int n;
int x[maxn];
i64 t[maxn];
i64 shr[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    cin >> n;
    forn(i, n) {
        cin >> x[i];
        string s1, s2;
        cin >> s1 >> s2;
        shr[i] = t[i] = get_date(s1, s2);
    }
    sort(shr, shr+n);
    forn(i, n) {
        cout << add(lower_bound(shr, shr+n, t[i]) - shr, x[i]) << "\n";
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
