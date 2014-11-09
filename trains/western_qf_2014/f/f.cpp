#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstring>
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

i64 fs[] = {0,
    1ll, 2ll, 6ll, 24ll, 120ll, 720ll, 5040ll, 40320ll, 362880ll, 3628800ll, 39916800ll, 479001600ll, 6227020800ll, 87178291200ll, 1307674368000ll};
const char *ns = "0123456789ABCDEFGHIJKLMNOQRST";

void print(i64 x) {
    int k = 1;
    while (fs[k+1] <= x) {
        ++k;
    }
    for (int i = k; i >= 1; --i) {
        printf("%c", ns[x/fs[i]]);
        x %= fs[i];
    }
    printf("\n");
}

char _s[100000];

void solve() {
    scanf("%s", _s);
    int n = strlen(_s);
    reverse(_s, _s+n);
    char *s = _s;
    s[n] = '+';
    i64 res = 0;
    i64 cur = 0;
    int p = 1;
    while (*s) {
        if (*s == '+') {
            res += cur;
            cur = 0;
            p = 1;
        } else if (*s == '-') {
            res -= cur;
            cur = 0;
            p = 1;
        } else {
            int t;
            if (isalpha(*s)) t = 10 + *s - 'A';
            else t = *s - '0';
            cur += fs[p] * t;
            ++p;
        }
        ++s;
    }
    assert(cur == 0);
    print(res);
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
