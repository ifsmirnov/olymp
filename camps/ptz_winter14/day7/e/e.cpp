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

struct T {
    int x, y, z;
    T(){}
    T(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator<(const T& t) const {
        if (x != t.x) return x < t.x;
        if (y != t.y) return y < t.y;
        return z != t.z;
    }
    void norm() {
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);
    }
};
map<T, int> d;
int go(T t) {
    t.norm();
    if (t.z < 0) return true;
    if (t.y == 0) return false;
    if (d.count(t)) return d[t];
    int& res = d[t];
    res = false;
    if (!go(T(t.x - 1, t.y - 1, t.z))) res = true;
    else if (!go(T(t.x - 1, t.y, t.z - 1))) res = true;
    else if (!go(T(t.x, t.y - 1, t.z - 1))) res = true;
    return res;
}

void solve() {
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    /*cout << "winners" << endl;
    forn(a, 10) forn(b, a+1) forn(c, b+1) {
        if (!go(T(a,b,c))) cout << a << " " << b << " " << c << endl;
    }*/
    while (true) {
    vi a(3);
    forn(i, 3) if (!(cin >> a[i])) return 0;
    sort(all(a));
    bool win;
    if (a[2] % 2 == 1) {
        win = (a[0] & 1) && (a[1] & 1) && (a[0] != 1);
    } else {
        win = (!(a[0] & 1) || a[0] == 1) && !(a[1] & 1);
    }
    win |= (a[0] == 0) && (a[1] == 0);
    assert(win);
    //cout << (win ? "Petya" : "Masha") << '\n';
}
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
