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

char buf[maxn];

void dt(char *b, int n, int d) {
    int k = 0;
    for (int rem = 0; rem < d; ++rem) {
        for (int i = rem; i < n; i += d) {
            buf[k++] = b[i];
        }
    }
    assert(k == n);
    forn(i, n) {
        b[i] = buf[i];
    }
}

void dtk(char *b, int n, int d, int k) {
    forn(i, n-k+1) {
        dt(b+i, k, d);
    }
}

int n;
char s[maxn];

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    n = 30;
    s[n] = '\0';
    while (1) {
        int k, d;
        cin >> k >> d;
        forn(i, n) s[i] = i;
        dtk(s, n, d, k);
        forn(i, n) {
            cout << (int)s[i] << " ";
        }
        cout << endl;
//         cout << s << endl << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
