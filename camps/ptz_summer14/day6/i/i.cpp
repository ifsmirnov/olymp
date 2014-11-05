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
#include <unordered_map>
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

const int mod = 1000000087;

const int hashp = 395821;
const int maxk = 40400;
const int maxn = 21;

vector<int> pts;
int vals[maxk][maxn + 1];
u64 hashes[maxk];
int a[maxk][maxn + 1];
int b[maxn + 1], bval[maxn + 1];
int n, m, k;

int countvalue(int *a, int deg, int x)
{
    i64 ans = 0;
    for (int j = deg; j >= 0; --j)
    {
        ans = ans * x + a[j];
        if (ans >= mod) ans %= mod;
    }
    return ans;
}

int power(int x, int p)
{
    i64 cur = x, ans = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
        {
            ans = ans * cur;
            if (ans >= mod) ans %= mod;
        }
        cur = cur * cur;
        if (cur >= mod) cur %= mod;
    }
    return ans;
}

const int hsize = 1 << 17, hmsk = hsize - 1;

int tg[hsize], curt = 0;

struct node
{
    u64 fi;
    int se;
};

node table[hsize];

inline int get(u64 x)
{
    int pos = x & hmsk;
    while (tg[pos] == curt)
    {
        if (table[pos].fi == x) return table[pos].se;
        if (++pos == hsize) pos = 0;
    }
    return 0;
}

int gcdex(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int xx, yy;
    int g = gcdex(b, a % b, xx, yy);
    x = yy;
    y = (g - (i64) a * x) / b;
//     cout << a << " " << b << " " << x << " " << y << " " << g << endl;
    return g;
}

int inv(int a)
{
    int x, y;
    gcdex(a, mod, x, y);
    if (x < 0) x += mod;
    return x;
}

inline void clear()
{
    curt++;
}

inline void inc(u64 x)
{
    int pos = x & hmsk;
    while (tg[pos] == curt)
    {
        if (table[pos].fi == x)
        {
            ++table[pos].se;
            return;
        }
        if (++pos == hsize) pos = 0;
    }
    tg[pos] = curt;
    table[pos].fi = x;
    table[pos].se = 1;
}

int cntz = 0;

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    srand(9349);
    scanf("%d%d%d", &k, &m, &n);
//     k = 40000; m = 150; n = 20;
    for (int i = 0; i < k; ++i)
    {
        bool x = true;
        for (int j = 0; j <= n; ++j)
        {
            scanf("%d", &a[i][j]);
//             a[i][j] = rand() % 1000000 + 1;
            if (a[i][j] < 0) a[i][j] += mod;
            x &= a[i][j] == 0;
        }
        if (x) --i, --k, ++cntz;
    }
    const int K = 21;
    while ((int) pts.size() < K)
    {
        int pt = ((rand() * RAND_MAX) + rand()) % mod;
        if (pt < 0) pt += mod;
        bool fail = false;
        for (int i = 0; i < k; ++i)
        {
            i64 ans = countvalue(a[i], n, pt);
            vals[i][pts.size()] = ans;
            if (ans == 0)
            {
                fail = true;
                break;
            }
        }
        if (!fail)
        {
            for (int i = 0; i < k; ++i)
            {
                hashes[i] = hashes[i] * hashp + vals[i][pts.size()];
//                 vals[i][pts.size()] = power(vals[i][pts.size()], mod - 2);
                vals[i][pts.size()] = inv(vals[i][pts.size()]);
            }
            pts.pb(pt);
        }
    }
//     cout << "time = " << clock()/1000 << endl;
//     cout << pts.size() << endl;
//     for (int i = 0; i < k; ++i) cout << hashes[i] << " ";
//     cout << endl;
    for (int it = 0; it < m; ++it)
    {
        clear();
        bool x = true;
        for (int j = 0; j <= 2 * n; ++j)
        {
            scanf("%d", &b[j]);
//             b[j] = rand() % 1000000 + 1;
            if (b[j] < 0) b[j] += mod;
            x &= b[j] == 0;
        }
        if (x)
        {
            cout << cntz * (cntz + 1) / 2 + cntz * k << endl;
            continue;
        }
        for (int i = 0; i < (int) pts.size(); ++i)
            bval[i] = countvalue(b, 2 * n, pts[i]);

        int ans = 0;
        for (int i = 0; i < k; ++i)
        {
            inc(hashes[i]);
            u64 hash = 0;
            for (int j = 0; j < (int) pts.size(); ++j)
            {
                int cur = (u64) bval[j] * vals[i][j] % mod;
                hash = hash * hashp + cur;
            }
            ans += get(hash);
        }
        printf("%d\n", ans);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
