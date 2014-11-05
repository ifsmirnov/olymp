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

int position(char *s) {
    return 8 * (s[1] - '1') +  (s[0] - 'a');
}

int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

bool cor(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}
u64 least[64], beat[64];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);

    int T;
    //cin >> T;
    scanf("%d", &T);
    forn(i, 8) {
        forn(j, 8) {
            int p = 8 * i + j;
            int m = 64;
            forn(d, 8) {
                int x = i + dx[d], y = j + dy[d];
                if (cor(x, y)) {
                    int pp = 8 * x + y;
                    //least[p] = least[p] ? min(least[p], 1ULL << pp) : (1ULL << pp);
                    m = min(m, pp);
                    beat[p] += 1ULL << pp;
                }
            }
            least[m] |= 1LL << p;
        }
    }
    while (T-->0) {
        int N;
        //cin >> N;
        scanf("%d", &N);
        u64 mask = 0;
        forn(i, N) {
            //string p;
            char s[5];
            //cin >> p;
            scanf("%s", s);
            mask |= 1ULL << position(s);
        }
        //vector<bool> kn(64, true);
        u64 ans = 0;
        for (int i = 63; i >= 0; --i) {
            if (mask & least[i]) {
                //cerr << i << ' ' << least[i] << '\n';
                ans |= 1ULL << i;
                mask &= ~beat[i];
            }
        }
        cout << ans << '\n';
        //printf("%
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}

