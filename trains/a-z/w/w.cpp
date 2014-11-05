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

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    freopen("widows.in", "r", stdin);
    freopen("widows.out", "w", stdout);
    int mnx = 10000, mny = 10000, mxx = -10000, mxy = -10000;
    int n;
    cin >> n;
    int x1, y1, x2, y2;
    forn(i, n) {
        cin >> x1 >> y1 >> x2 >> y2;
        mnx = min(mnx, x2);
        mny = min(mny, y2);
        mxx = max(mxx, x1);
        mxy = max(mxy, y1);
    }
    if (mxx <= mnx && mxy <= mny) {
        cout << (mnx-mxx) * (mny-mxy) << endl;
    } else {
        cout << 0 << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
