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

int dp[maxn + 1][maxn + 1][4 * maxn + 1], back[maxn + 1][maxn + 1][4 * maxn + 1];
int data[maxn];
string s, t;

int gettype(char c)
{
        if (c == 'A') return 0;
            if (c == 'C') return 1;
                if (c == 'G') return 2;
                    if (c == 'T') return 3;
                        assert(false);
}

int main() {
#ifdef HOME
        freopen("input.txt", "r", stdin);
#else
            freopen("transform.in", "r", stdin);
                freopen("transform.out", "w", stdout);
#endif
                    cin >> s >> t;
                        int n = s.length();
                            for (int i = 0; i < n; ++i)
                                        data[i] = (gettype(s[i]) - gettype(t[i]) + 4) % 4;
                                            for (int i = n - 1; i >= 0; --i)
                                                        data[i] = (data[i] - data[i - 1] + 4) % 4;
                                                        //     printf("%d ", data[i]);
                                                        //     printf("\n");

                                                            memset(dp, 127, sizeof(dp));
                                                                dp[0][0][0] = 0;
                                                                    for (int i = 0; i < n; ++i)
                                                                                for (int b = 0; b <= 4 * i; ++b)
                                                                                                for (int o = 0; o <= i; ++o)
                                                                                                                    for (int c = -3; c <= 3; ++c)
                                                                                                                                        {
                                                                                                                                                                int no = o + (c > 0 ? 1 : 0);
                                                                                                                                                                                    if ((data[i] + c + 4) % 4 == 0 && b + c >= 0 &&
                                                                                                                                                                                                                dp[i + 1][no][b + c] > dp[i][o][b] + (c < 0 ? 1 : 0))
                                                                                                                                                                                                            {
                                                                                                                                                                                                                                        dp[i + 1][no][b + c] = dp[i][o][b] + (c < 0 ? 1 : 0),
                                                                                                                                                                                                                                                                back[i + 1][no][b + c] = c;
                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                    int ansv = 1000000000, curo = -1, curb = -1;
                                                                                                                                                                                                                                                                                                        for (int i = 0; i <= n; ++i)
                                                                                                                                                                                                                                                                                                                    for (int j = 0; j <= 4 * i; ++j)
                                                                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                                                                                if (max(i, dp[n][i][j] + (j + 3) / 4) < ansv)
                                                                                                                                                                                                                                                                                                                                                                    ansv = max(i, dp[n][i][j] + (j + 3) / 4), curo = i, curb = j;
                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                printf("%d\n", ansv);
                                                                                                                                                                                                                                                                                                                                                                                    vector<segm> ans;
                                                                                                                                                                                                                                                                                                                                                                                        vector< pair<int, int> > close;
                                                                                                                                                                                                                                                                                                                                                                                            close.pb(mp(n, curb));
                                                                                                                                                                                                                                                                                                                                                                                                while (n > 0)
                                                                                                                                                                                                                                                                                                                                                                                                        {
                                                                                                                                                                                                                                                                                                                                                                                                                    int c = back[n][curo][curb];
                                                                                                                                                                                                                                                                                                                                                                                                                            if (c < 0) close.pb(mp(n - 1, -c));
                                                                                                                                                                                                                                                                                                                                                                                                                                    if (c > 0)
                                                                                                                                                                                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                int curc = c;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                            while (curc > 0)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                int x = min(close.back().second, curc);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                ans.pb(segm(n - 1, close.back().first, x));
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                close.back().second -= x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                if (close.back().second == 0)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        close.pop_back();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        curc -= x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                --curo;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                curb -= c;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        --n;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                assert((int) ans.size() == ansv);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    for (size_t i = 0; i < ans.size(); ++i)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                cout << ans[i].l + 1 << " " << ans[i].r << " " << ans[i].v << endl;
#ifdef HOME
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        return 0;
}
