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
const int maxn = 100500;

i64 f(i64 x) {
    return x - (i64)floor(sqrt(1.0 * x));
}

i64 low(i64 x) {
    i64 y = x + (i64)floor(sqrt(1.0 * x));
    while (f(y) <= x) ++y;
    return y;
}

int main() {
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
    i64 N;
    i64 last = 0;
    cin >> N;
    i64 q = 0;
    bool lose = false;
    while (last <= N) {
        //cout << last << '\n';
        if (last == N) lose = true;
        ++q;
        last = low(last);
    }
    cout << (lose ? "LOSE" : "WIN") << '\n';

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
