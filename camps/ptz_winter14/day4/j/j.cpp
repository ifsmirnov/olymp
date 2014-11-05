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

int n;
map<string, int> d;

int go(string s) {
    if (d.count(s)) return d[s];
    int& res = d[s];
    forn(p, s.length()) if (s[p] == 'N') {
//         cout << "p = " << p << endl;
        for (int d = 1; d <= (int)s.length()-p; ++d) {
            int cc = (s.length() - p + d - 1) / d;
//             cout << "d = " << d << ", cc = " << cc << endl;
            for (int C = 1; C <= cc; ++C) {
                string g(s);
                forn(j, C) g[p+j*d] ^= 'N'^'S';
//                 cout << "g = " << g << endl;
//                 continue;
                if (!go(g)) return res = 1;
            }
        }
    }
    return res = 0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

//     cout << go("NSNNS") << endl;
//     return 0;

    for (int n = 4; n <= 20; ++n) if (n != 7&& n != 9) {
//     cout << "WIN" << endl;
//     forn(i, 1<<n) {
//         string s(n, '0');
//         forn(j, n) s[j] = "SN"[(bool)(i&(1<<j))];
//         if (go(s)) cout << s << endl;
//     }
        d.clear();
        int cnt = 0;
//         cout << "LOSE" << endl;
        cout << n << ": ";
        vector<string> t;
        forn(i, 1<<n) {
            string s(n, '0');
            forn(j, n) s[n-j-1] = "SN"[(bool)(i&(1<<j))];
            if (s[0] == 'N' && !go(s)) {
                t.pb(s);
                cout << s << endl;
                ++cnt;
                break;
            }
        }
    //     sort(all(t));
    //     forn(i, t.size()) cout << t[i] << endl;
//         cout << n << ": " << cnt << endl;
//         cout << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
