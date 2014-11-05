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
#include <cstring>
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
const int maxn = 110;

struct segm
{
    int l, r, v;

    segm(int nl, int nr, int na): l(nl), r(nr), v(na) {}
};

// int dp[maxn + 1][maxn + 1][4 * maxn + 1], back[maxn + 1][maxn + 1][4 * maxn + 1];
int data[maxn], n;
string s, t;

int gettype(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    assert(false);
}

// inline bool cmp(const pii &a, const pii &b)
// {
//     return a.second > b.second;
// }

vector<segm> ans;

int putSegm(int a, int b)
{
    if (a > b) swap(a, b);
    if (b == n)
    {
        assert(data[a] != 0);
        if (data[a])
            ans.pb(segm(a, n - 1, 4 - data[a]));
        data[a] = 0;
    }
    else if (data[a] == 1 && data[b] == 3)
    {
        ans.pb(segm(a, b - 1, 3));
        data[a] = data[b] = 0;
    }
    else if (data[a] == 3 && data[b] == 1)
    {
        ans.pb(segm(a, b - 1, 1));
        data[a] = data[b] = 0;
    }
    else if (data[a] == 1 && data[b] == 1)
    {
        ans.pb(segm(a, b - 1, 1));
        data[a] = 2, data[b] = 0;
    }
    else if (data[a] == 3 && data[b] == 3)
    {
        ans.pb(segm(a, b - 1, 3));
        data[a] = 2, data[b] = 0;
    }
    else if (data[a] == 2 && data[b] == 2)
    {
        ans.pb(segm(a, b - 1, 2));
        data[a] = 0, data[b] = 0;
    }
    return a;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#else
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
#endif
    cin >> s >> t, n = s.length();
    for (int i = 0; i < n; ++i)
        data[i] = (gettype(s[i]) - gettype(t[i]) + 4) % 4;
    for (int i = n - 1; i >= 0; --i)
        data[i] = (data[i] - data[i - 1] + 4) % 4;
//     for (int i = 0; i < n; ++i)
//         printf("%d ", data[i]);
//    printf("\n");

    vector<int> on, tr, tw;
    for (int i = 0; i < n; ++i)
        if (data[i] == 1) on.pb(i);
        else if (data[i] == 3) tr.pb(i);
        else if (data[i] == 2) tw.pb(i);
    for (; min(on.size(), tr.size()) > 0;)
        putSegm(on.back(), tr.back()), on.pop_back(), tr.pop_back();
    for (; on.size() > 1;)
    {
        tw.push_back(putSegm(on[on.size() - 1], on[on.size() - 2]));
        on.pop_back(), on.pop_back();
    }
    for (; tr.size() > 1;)
    {
        tw.push_back(putSegm(tr[tr.size() - 1], tr[tr.size() - 2]));
        tr.pop_back(), tr.pop_back();
    }
    for (; tw.size() > 1;)
    {
        putSegm(tw[tw.size() - 1], tw[tw.size() - 2]);
        tw.pop_back(), tw.pop_back();
    }
    for (size_t i = 0; i < on.size(); ++i)
        putSegm(on[i], n);
    for (size_t i = 0; i < tw.size(); ++i)
        putSegm(tw[i], n);
    for (size_t i = 0; i < tr.size(); ++i)
        putSegm(tr[i], n);

//     memset(dp, 127, sizeof(dp));
//     dp[0][0][0] = 0;
//     for (int i = 0; i <= n; ++i)
//         for (int b = 0; b <= 4 * i; ++b)
//             for (int o = 0; o <= i; ++o)
//             {
//                 if (dp[i][o][b] > 100000000) continue;
//                 printf("dp[%d][%d][%d] = %d\n", i, o, b, dp[i][o][b]);
//                 if (i == n) continue;
//                 if (dp[i][o + 1][b + 4] > dp[i][o][b])
//                 {
//                     dp[i][o + 1][b + 4] = dp[i][o][b];
//                     back[i][o + 1][b + 4] = 4;
//                 }
//                 for (int c = -3; c <= 3; ++c)
//                 {
//                     int no = o + (c > 0 ? 1 : 0);
//                     if ((data[i] + c + 4) % 4 == 0 && b + c >= 0 &&
//                         dp[i + 1][no][b + c] > dp[i][o][b] + (c < 0 ? 1 : 0))
//                     {
//                         dp[i + 1][no][b + c] = dp[i][o][b] + (c < 0 ? 1 : 0),
//                         back[i + 1][no][b + c] = c;
//                     }
//                 }
//             }
//     int ansv = 1000000000, curo = -1, curb = -1;
//     for (int i = 0; i <= n; ++i)
//         for (int j = 0; j <= 4 * i; ++j)
//         {
//             if (max(i, dp[n][i][j] + (j + 3) / 4) < ansv)
//                 ansv = max(i, dp[n][i][j] + (j + 3) / 4),
//                 curo = i, curb = j;
//         }
//     printf("%d\n", ansv);
//     vector<segm> ans;
//     vector< pair<int, int> > close;
//     close.pb(mp(n, curb));
//     cout << curo << " " << curb << endl;
//     cout << "----" << endl;
//     while (n > 0)
//     {
//         int c = back[n][curo][curb];
//         cout << n << " " << curo << " " << curb << " " << c << endl;
//         if (c < 0) close.pb(mp(n - 1, -c));
//         if (c > 0)
//         {
//             int curc = c;
//             while (curc > 0)
//             {
//                 sort(close.begin(), close.end(), cmp);
//                 int x = min(close.back().second, curc);
//                 ans.pb(segm(n - 1, close.back().first, x));
//                 close.back().second -= x;
//                 if (close.back().second == 0)
//                     close.pop_back();
//                 curc -= x;
//             }
//             --curo;
//         }
//         curb -= c;
//         if (c != 4) --n;
//     }
// //     assert((int) ans.size() == ansv);
    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); ++i)
        cout << ans[i].l + 1 << " " << ans[i].r + 1 << " " << ans[i].v << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
