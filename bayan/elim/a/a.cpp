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

int c[3];

void solve() {
    forn(i, 3) c[i] = 0;
    string s;
    int n;
    cin >> n;
    cin >> s;
    assert(n == (int)s.length());
    forn(i, n) {
        char x = s[i];
        if (x == 'R') ++c[0];
        else if (x == 'S') ++c[1];
        else if (x == 'P') ++c[2];
        else assert(false);
    }
//     forn(i, 3) cout << c[i] << " "; cout << endl;
    int mx = 0;
    forn(i, 3) if (c[i] && c[(i+1)%3]) mx = max(mx, c[(i+1)%3]);
    int res = 0;
    forn(i, 3) if (c[(i+1)%3] == mx) res += c[i];
    assert(res <= (int)s.length());
    cout << res << endl;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
//     freopen("A.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    fore(i, 1, t) {
        cout << "Case #" << i << ":\n";
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
