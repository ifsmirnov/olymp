#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
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

const int maxn = 2020;

int n, m;
char data[maxn][maxn + 1];
vector<int> occ[maxn];
int cnt[maxn];
set<int> brd;
vector<pii> events;

inline int getdist(const set<int>::iterator &pos)
{
    if (*pos >= 0 && *pos < m && cnt[*pos] != 1) return 0;
    set<int>::iterator it = pos, jt = pos;
    if (it != brd.begin()) --it;
    if (++jt == brd.end()) --jt;
//     cout << brd.size() << " " << *it << " " << *jt << " " << *jt - *it - 1 << endl;
    return *jt - *it - 1;
}

int stress()
{
    int ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            for (int z = 0; z < m; ++z)
                for (int k = z; k < m; ++k)
                {
                    int cnt = 0;
                    for (int a = i; a <= j; ++a)
                        for (int b = z; b <= k; ++b)
                            cnt += data[a][b] == '#' ? 1 : 0;
                    if (cnt <= 1)
                        ans = max(ans, (j - i + 1) * (k - z + 1));
                }
    return ans;
}

void gen(int n, int m)
{
    FILE *f = fopen("test.txt", "w");
    fprintf(f, "%d %d\n", n, m);
    for (int i = 0; i < n; ++i, fprintf(f, "\n"))
        for (int j = 0; j < m; ++j)
            fprintf(f, "%c", (rand() & 15) ? '.' : '#');
    fclose(f);
}

int main()
{
#ifdef HOME
    long long seed;
    asm("rdtsc":"=A"(seed));
    srand(seed);
    gen(10, 10);
    freopen("test.txt", "r", stdin);
#endif
    scanf("%d%d\n", &n, &m);
    int q = 0;
    for (int i = 0; i < n; ++i)
    {
        gets(data[i]);
        for (int j = 0; j < m; ++j)
            if (data[i][j] == '#')
                occ[j].pb(i), ++q;
    }
    int ans = 0;
    for (int l = 0; l < n; ++l)
    {
        events.clear();
        for (int i = 0; i < m; ++i)
        {
            int ptr = lower_bound(all(occ[i]), l) - occ[i].begin();
            for (int j = ptr; j < ptr + 2 && j < (int) occ[i].size(); ++j)
                events.pb(mp(occ[i][j], i));
        }

        sort(all(events));
        brd.clear();
        memset(cnt, 0, sizeof(cnt));
        brd.insert(-1), brd.insert(m);
//         cout << events.size() << endl;
//         cout << events[0].fi << " " << events[0].se << endl;
        for (size_t i = 0; i < events.size();)
        {
            size_t j = i;
            while (j < events.size() && events[i].fi == events[j].fi)
            {
                pii ev = events[j];
//                 cout << ev.fi << " " << ev.se << endl;
                int dx = ev.fi - l;
//                 cout << "dx = " << dx << endl;
                if (cnt[ev.se] == 1)
                    ans = max(ans, dx * getdist(brd.find(ev.se)));
                else if (cnt[ev.se] == 0)
                {
                    set<int>::iterator it = brd.lower_bound(ev.se), jt = it;
                    assert(it != brd.begin());
                    assert(it != brd.end());
                    --jt;
                    ans = max(ans, dx * getdist(it));
                    ans = max(ans, dx * getdist(jt));
                    ans = max(ans, dx * (*it - *jt - 1));
                }
                else assert(false);
                ++j;
            }
//             cout << "ans = " << ans << endl;
//             cout << "------" << endl;
            for (size_t z = i; z < j; ++z)
            {
                pii ev = events[z];
                ++cnt[ev.se];
                brd.insert(ev.se);
            }
            i = j;
        }
        int dx = n - l;
        auto prev = brd.begin();
        for (auto it = brd.begin(); it != brd.end(); ++it)
        {
            if (cnt[*it] == 1)
                ans = max(ans, dx * getdist(it));
            ans = max(ans, dx * (*it - *prev - 1));
            prev = it;
        }
    }
    if (q == 0) ans = n * m;
    printf("%d\n", ans);
#ifdef HOME
    if (n <= 10 && m <= 10)
        assert(ans == stress());
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
