zzyzx
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
#include <queue>
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
typedef vector<vi> vvi;


int n;

map<vector<vi>, i64> d;
map<vector<vi>, vector<vi> > anc;
queue<vvi> q;
bool ok(const vvi& a) {
    if (a[0].size() == (size_t)n*2) {
        bool ok = true;
        forn(i, a[0].size() - 1) {
            if (a[0][i] != 2*n-i-1) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

void path(vvi a) {
    while (anc.count(a)) {
        forn(i, 3) {
            forn(j, a[i].size()) cout << a[i][j] << " "; cout << endl;
        }
        cout << "----\n";
        a = anc[a];
    }
}

i64 bfs(vvi start) {
    d.clear();
    d[start] = 0;
    while (!q.empty()) q.pop();
    q.push(start);

    while (!q.empty()) {
        vvi a = q.front();
        vvi b = a;
        q.pop();

        i64 md = d[a];
        if (ok(a)) {
            path(a);
            return md;
        }

        forn(i, 3) forn(j, 3) if (!a[i].empty() && i != j) {
            if (a[j].empty() || a[i].back() / 2 <= a[j].back() / 2) {
                a[j].pb(a[i].back());
                a[i].pop_back();

                if (!d.count(a)) {
                    anc[a] = b;
                    d[a] = md + 1;
                    q.push(a);
                }

                a[i].pb(a[j].back());
                a[j].pop_back();
            }
        }
    }
    assert(false && "Path not found");
}

int a[maxn];
int bs[maxn];
i64 getb(int n) {
    if (n == 0) return 0;
    i64 res = 1;
    forn(i, n+1) res <<= 1;
    return res - 2;
}
i64 geta(int n) {
    if (n == 0) return 0;
    i64 A = geta(n-1);
    i64 B = getb(n-1);
    cout << "n = " << n << ": "  << A << " " << B << endl;
    if (bs[n-1]) {
        return A + B + 2;
    } else {
        return A + 3*B + 3;
    }
}

void scan() {
    scanf("%d", &n);
    forn(i, n) {
        scanf("%d%d", &a[i*2], &a[i*2+1]);
        a[i*2]--;
        a[i*2+1]--;
    }
    reverse(a, a+n*2);
    forn(i, n) {
        bs[i] = !(a[i*2]%2);
    }
    bs[n-1] ^= 1;
}


i64 solved() {
    vector<vi> a(3);
    a[1] = vi(::a, ::a+2*n);
    reverse(all(a[1]));
    return bfs(a);
}
i64 solve() {
    return geta(n);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    cout << solved() << endl;
    //cout << solve() << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
