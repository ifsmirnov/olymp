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

ostream& operator<<(ostream& out, const vi& a) {
    forn(i, a.size()) out << a[i] << " ";
    return out;
}

int n;
set<vi> d;

vi rot(vi a) {
    rotate(a.begin(), a.begin()+1, a.end());
    return a;
}
vi s4(vi a) {
    swap(a[0], a[3]);
    swap(a[1], a[2]);
    return a;
}
vi s4(vi a, int k) {
    swap(a[k], a[(k+3)%a.size()]);
    swap(a[(k+1)%a.size()], a[(k+2)%a.size()]);
    return a;

}
vi id(int n) {
    vi a(n);
    forn(i, n) a[i] = i;
    return a;
}

void dfs(const vi &a) {
    vi b = rot(a);
    if (!d.count(b)) {
        d.insert(b);
        dfs(b);
    }
    b = s4(a);
    if (!d.count(b)) {
        d.insert(b);
        dfs(b);
    }
}

void solve() {
    n = 4;
    d.insert(id(n));
    dfs(id(n));
    cout << d.size() << endl;
    for (auto i: d) {
        cout << i << endl;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
