#include <iostream>
#include <cstdio>
#include <sstream>
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
        return z < t.z;
    }
    bool operator==(const T& t) const {
        return x == t.x && y == t.y && z == t.z;
    }
    void norm() {
        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);
        assert(x<=y && y<=z);
    }
};
int cntg = 0;
map<T, int> d;
int go(T t) {
    t.norm();
    if (t.x < 0 || t.y < 0 || t.z < 0) return true;
    if (t.y == 0 && t.x == 0) return false;
    if (d.count(t)) return d[t];
    ++cntg;
    int& res = d[t];
//     cerr << t.x << " " << t.y << " " << t.z << endl;
    res = false;
    if (!go(T(t.x - 1, t.y - 1, t.z))) res = true;
    else if (!go(T(t.x - 1, t.y, t.z - 1))) res = true;
    else if (!go(T(t.x, t.y - 1, t.z - 1))) res = true;
    return res;
}

set<vi> win;

string s = "\
0 0 3 \
0 1 1 \
0 1 2 \
0 1 3 \
0 2 1 \
0 3 0 \
0 3 1 \
0 3 3 \
1 0 1 \
1 0 2 \
1 0 3 \
1 1 0 \
1 1 1 \
1 1 2 \
1 2 0 \
1 2 1 \
1 2 3 \
1 3 0 \
1 3 2 \
1 3 3 \
2 0 1 \
2 1 0 \
2 1 1 \
2 1 3 \
2 2 3 \
2 3 1 \
2 3 2 \
2 3 3 \
3 0 0 \
3 0 1 \
3 0 3 \
3 1 0 \
3 1 2 \
3 1 3 \
3 2 1 \
3 2 2 \
3 2 3 \
3 3 0 \
3 3 1 \
3 3 2 \
";

int main() {
#ifdef HOME
//     freopen("input.txt", "w", stdout);
#endif

    stringstream ss(s);
    forn(i, 40) {
        vi a(3);
        forn(j, 3) ss >> a[j];
        win.insert(a);
    }


    vi t(3);
    forn(i, 3) cin >> t[i];
    sort(all(t));
    t[2] = min(t[2], t[0]+t[1]);
    forn(i, 3) t[i] %= 4;
    if (win.count(t)) cout << "Masha" << endl;
    else cout << "Petya" << endl;
    return 0;
//     cout << go(T(a,b,c)) << endl;
// 
//     cerr << "cntg = " << cntg << endl;
//     cerr << d.size() << endl;

//     for (auto z: d) {
//         cerr << z.fi.x << " " << z.fi.y << " " << z.fi.z << endl;
//     }
// 
//     while (1) {
//         int a, b, c;
//         if (!(cin >> a >> b >> c)) break;
//         if (a>b) swap(a,b);
//         if (b>c) swap(b,c);
//         if (a>b) swap(a,b);
//         assert(a<=b&&b<=c);
//         c = min(c, a+b);
//         cout << (go(T(a%4, b%4, c%4)) ? "Masha" : "Petya") << endl;
//     }
//     return 0;
//     cout << "winners" << endl;
//     vector<T> t;
//     forn(a, 13) forn(b, a+1) forn(c, b+1) if (a <= b+c) {
//         if (b == 0 && c == 0) cerr << a << endl;
//         if (go(T(a,b,c))) {
//             t.pb(T(a,b,c));
//         }
//     }
//     forn(i, t.size()) {
//         t[i].norm();
//         t[i].x %= 4;
//         t[i].y %= 4;
//         t[i].z %= 4;
//     }
//     sort(all(t));
//     t.erase(unique(all(t)), t.end());
//     forn(i, t.size()) {
//         cout << t[i].x%4 << " " << t[i].y%4 << " " << t[i].z%4 << endl;
//     }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
