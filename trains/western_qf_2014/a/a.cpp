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

int pr[100000], npr;

bool prime(int x) {
    for (int i = 2; i*i <= x; ++i) {
        if (x%i == 0) {
            return false;
        }
    }return true;
}

void gen() {
    for (int x = 2; x < 50000; ++x) {
        if (prime(x)) {
            pr[npr++] = x;
        }
    }
}

i64 f(int x) {
    int y = x;
    i64 res = 0;
    for (int i = 0; i < npr && pr[i] * pr[i] <= x; ++i) {
        while (x % pr[i] == 0) {
            res += y / pr[i];
            x /= pr[i];
        }
    }
    if (x != 1) {
        res += y / x;
    }
    return res;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    gen();
    int t;
    scanf("%d", &t);
    forn(i, t) {
        int x;
        scanf("%d", &x);
        printf("%lld\n", f(x));
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
