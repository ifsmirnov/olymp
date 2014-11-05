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
#define  op operator

const int maxn = 305;

struct pt {
    int x, y;
    pt(){}
    pt(int x, int y):x(x), y(y) {}
    pt op+(const pt& p) const { return pt(x+p.x, y+p.y); }
    pt op-(const pt& p) const { return pt(x-p.x, y-p.y); }
    i64 op*(const pt& p) const { return (i64)x*p.y - (i64)y*p.x; }
    pt op-() const { return pt(-x, -y); }
    bool op<(const pt& p) const { return x < p.x || (x == p.x && y < p.y); }
    bool op==(const pt& p) const { return x == p.x && y == p.y; }
};

int n;
pt p[maxn];

bool check_on_line() {
    forn(i, n) forn(j, i) {
        i64 a = p[i].y - p[j].y;
        i64 b = p[j].x - p[i].x;
        i64 c = -(a*p[i].x + b*p[i].y);
        int cnt = 0;
        forn(k, n) {
            cnt += (a*p[k].x + b*p[k].y + c != 0);
            if (cnt > 1) break;
        }
        if (cnt <= 1) return true;
    }
    return false;
}

bool check_par() {
    if (n < 3) return true;
    sort(p, p+n);
    if (n == 4) {
        return (p[1] - p[0]) == (p[3] - p[2]);
    } else if (n == 5) {
        return (p[1] - p[0]) == (p[4] - p[3]) && (p[2] - p[0]) == (p[4] - p[2]);
    } else {
        return false;
    }
}

int main() {
// #ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
// #endif

    cin >> n;
    forn(i, n) cin >> p[i].x >> p[i].y;
    if (n <= 3) {
        cout << n << endl;
    } else if (check_on_line()) {
        cout << n << endl;
    } else if (check_par()) {
        cout << 5 << endl;
    } else {
        cout << "oo" << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
