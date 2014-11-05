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

int p3[maxn];
int get_trit(int mask, int i);
int set_trit(int mask, int i, int val);

void initp3() {
    p3[0] = 1;
    forn(i, 10) p3[i + 1] = p3[i] * 3;
}

int get_trit(int mask, int i) {
    return mask / p3[i] % 3;
}

int set_trit(int mask, int i, int val) {
    return mask + (val - get_trit(mask, i)) * p3[i];
}

string s;
i64 d[20][60000][2];

void relax(i64 x, i64&y) {
    y += x;
}

i64 fd() {
    if (s.empty()) {
        return 0;
    }
    int n = s.length();
    forn(i, n+1) forn(mask, p3[10]) forn(b, 2) {
        d[i][mask][b] = 0;
    }
    d[0][0][0] = 1;
    forn(i, n) forn(mask, p3[10]) forn(b, 2) if (d[i][mask][b]) {
        int ulim = b ? 9 : s[i]-'0';
        fore(c, 0, ulim) if (c || i) {
            int trit = get_trit(mask, c);
            int nb = b || (c < ulim);
            if (trit != 2) {
                d[i+1][set_trit(mask, c, trit+1)][nb] += d[i][mask][b];
            }
        }
    }

    i64 res = 0;
    forn(mask, p3[10]) forn(b, 2) res += d[n][mask][b];
    if (n != 1) {
        s = string(n-1, '9');
        res += fd();
    }
    return res;
}

void sub1(string& s) {
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] == '0') s[i] = '9';
        else {
            --s[i];
            break;
        }
    }
    if (s[0] == '0' && s != "0") s = s.substr(1);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    freopen("exchange.in", "r", stdin);
    freopen("exchange.out", "w", stdout);

    initp3();

    cin >> s;
    sub1(s);
    i64 res = fd();
    cin >> s;
    res = fd() - res;
    cout << res << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
