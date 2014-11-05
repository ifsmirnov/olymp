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
#include <limits>
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

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#else
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

//     cout << numeric_limits<u64>::max() << endl;
//     cout << 1000000000000000000 << endl;

    int n;
    i64 x;
    cin >> n >> x;
    i64 t = 1;
    long double q = 1;
    bool correct = false;
    fore(i, 1, n) {
        t *= 2ll * i;
        q *= 2 * i;
        if (q > 1.01 * x || t >= x) {
            correct = true;
            cout << "Harshat Mata" << endl;
            break;
        }
    }
    if (!correct) {
        cout << "Nope" << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
