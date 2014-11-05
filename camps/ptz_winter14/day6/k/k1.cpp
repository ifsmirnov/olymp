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
const int maxn = 200500;

struct job
{
    i64 a, b, d;
    int id;

    inline bool operator < (const job &j) const
    {
        return d < j.d;
    }
};

inline void add(i64 d)
{
    forn(i, n) data[i].d += d;
}

int n, ans[2 * maxn];
job data[maxn];
i64 pb[maxn];

bool ok(i64 t)
{
    add(t);
    i64 curt = 0;
    forn(i, n) pb[i] = (i ? pb[i - 1] : 0) + data[i].b;
    for (int i = 0; i < n;)
    {
        int curr = i;
        i64 x = curt + f[0] + f[1] - (i ? pb[i - 1] : 0), curmax = -inf;
        while (curr < n)
        {
            curmax = max(data[curr].d - pb[curr] - x) - data[curr].a;
            if (curmax < 0) break;
            ++curr;
        }
        if (curr == i)
        {
            add(-t);
            return false;
        }
        curt += f[0] + f[1];
        fore(j, i, curr - 1) curt += data[j].a + data[j].b;
        fore(j, i, curr - 1) ans[pos++] = -data[j].id - 1;
        fore(j, i, curr - 1) ans[pos++] = data[j].id + 1;
        i = curr;
    }
    add(-t);
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    cin >> n >> f[0] >> f[1];
    for (int i = 0; i < n; ++i) 
        cin >> data[i].a >> data[i].b >> data[i].d, data[i].id = i;
    sort(data, data + n);
    i64 left = 0, right = 1e12;
    while (left < right)
    {
        i64 middle = (left + right) / 2;
        if (ok(middle)) right = middle;
        else left = middle + 1;
    }
    assert(ok(left));
    cout << left << endl;
    for (int i = 0; i < 2 * n; ++i) cout << ans[i] << " ";
    cout << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
