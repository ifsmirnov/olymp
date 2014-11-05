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
#include <cstring>
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
const int maxk = 50;

int n, k, m, need;
int cnt[maxk];
u64 msk[maxk];

bool solve1()
{
    if (n > 23) return false;
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i)
    {
        bool ok = false;
        for (int j = 0; j < k && !ok; ++j)
            ok |= __builtin_popcount((int) msk[j] ^ i) < m;
        if (ok) ++ans;
    }
    cout << ans << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return true;
}

int recans = 0;

#define bit(a,x) (((a)>>(x))&1ULL)

void rec(u64 cur, int p)
{
    if (p == n) return void(++recans);
    for (int b = 0; b < 2; ++b)
    {
        bool fail = true;
        for (int i = 0; i < k; ++i)
        {
            if (bit(msk[i], p) != b) ++cnt[i];
            fail &= cnt[i] > m - 1;
        }

        if (!fail)
            rec((cur << 1) | b, p + 1);

        for (int i = 0; i < k; ++i)
            if (bit(msk[i], p) != b)
                --cnt[i];
    }
}

bool solve2()
{
    if (m > 5) return false;
    memset(cnt, 0, sizeof(cnt));
    need = n;
    rec(0, 0);
    cout << recans << endl;
#ifdef HOME
//     cerr << 0.99 * recans << " " << 1.01 * recans << endl;
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return true;
}

u64 genrand()
{
    return rand();
    u64 msk = 0;
    for (int i = 0; i < 4; ++i)
        msk = (msk * RAND_MAX) | rand();
    return msk;
}

void solve3()
{
//     cerr << "RAND_MAX = " << RAND_MAX << endl;
    srand(time(0));
//     const int max_iter = 5000000 * 3;
    int iter = 0;
    int found = 0;
    while (true)
    {
        u64 q = genrand() & ((1ULL << n) - 1);
        for (int i = 0; i < k; ++i)
            if (__builtin_popcountll(q ^ msk[i]) < m)
            {
                ++found;
                break;
            }
        ++iter;
        if ((iter & ((1 << 17) - 1)) == 0)
        {
            if (clock() > 14 * CLOCKS_PER_SEC) break;

        }
    }
    if (!found) ++found;
//     cerr << "found " << found << " of " << max_iter << endl;
    long double ans = (1LL << n) * (long double) found / iter;
//  cout << "error = " << ans / (348997) << endl;
    cout.precision(20);
    cout << ans << endl;
}

char str[51];
int perm[51];

int main() {
    srand(time(0));
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("close.in", "r", stdin);
    freopen("close.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &m);
//     n = 23;
//     k = 50;
//     m = 5;
    for (int i = 0; i < n; ++i) perm[i] = i;
    random_shuffle(perm, perm + n);
    for (int i = 0; i < k; ++i)
    {
        scanf("%s", str);
//         for (int j = 0; j < n; ++j) str[j] = '0' + (rand() & 1);
//         str[n] = 0;
//         cout << str << endl;
        msk[i] = 0;
        for (int j = 0; j < n; ++j)
            msk[i] = (msk[i] << 1) | (str[perm[j]] - '0');
    }
    sort(msk, msk + k);
    k = unique(msk, msk + k) - msk;
    random_shuffle(msk, msk + k);
    if (solve1()) return 0;
    if (solve2()) return 0;
    solve3();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
