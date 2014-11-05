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

const int maxn = 200500;
const int logn = 20;

int pref[maxn], sum[logn][maxn];
vector<pii> segs;
int n, q, data[maxn];

int getsum(int l, int r)
{
    return pref[r + 1] - pref[l];
}

void getsegs(int ord, int rev, int tl, int tr, int l, int r)
{
    if (l == tl && r == tr)
    {
        segs.pb(mp(ord, rev));
        return;
    }
    int mid = (tl + tr) / 2;
    if (r <= mid)
        return getsegs(ord - 1, rev, tl, mid, l, r);
    if (l >= mid)
        return getsegs(ord - 1, 1 - rev, mid, tr, l, r);
    getsegs(ord - 1, rev, tl, mid, l, mid);
    getsegs(ord - 1, 1 - rev, mid, tr, mid, r);
}

int main()
{
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &data[i]);
    pref[0] = 0;
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + data[i - 1];
    for (int len = 1, it = 0; len <= n; len *= 2, ++it)
        for (int i = 0; i + len <= n; ++i)
        {
            if (len == 1) sum[it][i] = 0;
            else
                sum[it][i] = sum[it - 1][i] +
                             getsum(i + len / 2, i + len - 1) - sum[it - 1][i + len / 2];
        }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i)
    {
        int x, y, k;
        scanf("%d%d%d", &x, &y, &k), --x;
        segs.clear();
        getsegs(30, 0, 0, 1 << 30, y, y + k);
        int pos = x, ans = 0;
        for (pii &seg : segs)
        {
//             cout << "(" << seg.fi << " " << seg.se << ") ";
            if (seg.se)
                ans += getsum(pos, pos + (1 << seg.fi) - 1) - sum[seg.fi][pos];
            else
                ans += sum[seg.fi][pos];
            pos += 1 << seg.fi;
//             cout << ans << endl;
        }
//         cout << endl;
        printf("%d\n", ans);
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
