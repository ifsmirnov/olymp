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

void out(const vi& a) {
    forn(i, a.size()) cout << a[i] << " "; cout << endl;
}

vi rev(const vi& a) {
    vi b(a.size());
    forn(i, a.size()) b[a[i]] = i;
    return b;
}

vi gen(const vi &a) {
    vi b = rev(a);
    vi c(a.size());
    forn(i, a.size()) {
        int j = b[i];
        forn(jp, a.size()) {
            c[i] += (jp < j && a[jp] > i);
        }
    }
    return c;
}

vi restore(const vi& a) {
    vi b;
    ford(i, a.size()) {
        if (a[i] > (int)b.size()) {
            return vi();
        }
        b.insert(b.begin()+a[i], i);
    }
    return b;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
//     freopen("invers.in", "r", stdin);
//     freopen("invers.out", "w", stdout);

    vi inv;
    int x;
    while (cin >> x) {
        inv.pb(x);
    }

    vi a = restore(inv);

    out(gen(rev(a)));



#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
