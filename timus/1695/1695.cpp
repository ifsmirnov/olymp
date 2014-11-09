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
typedef unsigned u32;
const int inf = 1e9+100500;
const int maxn = 55;

const int N = 50;
const int K = 24;
const int P = (N-K) / 2;

class Timer {
public: Timer(string s) : s(s), t(clock()) {}
~Timer() {
#ifdef HOME
    cerr << "Time [" << s << "]: " << (clock()-t)/1000 << " ms" << endl;
#endif
}
string s;
time_t t;
};

int n;
i64 res;
int fr[maxn], fl[maxn];
char buf[maxn];
// int d[1<<K];
unsigned char d[(1<<K) * 3 + 10];
int sp;
int gr[2][1<<P], br[2][1<<P], gl[2][1<<P];

inline int& pos(int i) {
//     return d[i];
    if (i+1 == (1<<K)) return sp;
    return *(int*)(d + i*3);
}

inline int val(int i) {
//     return d[i];
    if (i+1 == (1<<K)) return sp;
    return pos(i) & 0x00ffffff;
}


void scan() {
    scanf("%d", &n);
    forn(i, N) {
        if (i < n) {
            scanf("%s", buf);
//             cout << buf << endl;
        } else {
            memset(buf, 0, sizeof buf);
        }
        forn(j, N) if (buf[j] == '1' || i == j) {
            if (j < K) {
                fr[i] |= 1<<j;
            } else {
                fl[i] |= 1<<(j-K);
            }
        }
    }
    res = n - N;
    n = N;
}

void up() {
    int b = 0;
    pos(0) = 1;
    forn(m, 1<<K) if (m) {
        pos(m) = val(m^(1<<b)) + val((m^(1<<b)) & fr[b]);
        if (!(m&(m+1))) {
            ++b;
        }
    }
}

void go2() {
    forn(j, 2) {
        int off = K + P*j;
        br[j][0] = 1;
        gr[j][0] = (1<<K) - 1;
        gl[j][0] = (1<<P) - 1;
        int b = 0;
        forn(m, 1<<P) if (m) {
            int s = m^(1<<b);
            int rs = s << (j*P);
            if (br[j][s] && (fl[b+off] & rs) == rs) {
                br[j][m] = 1;
                gr[j][m] = gr[j][s] & fr[b+off];
                if (j == 0) {
                    gl[j][m] = gl[j][s] & (fl[b+off] >> P);
                }
            }
            if (!(m&(m+1))) {
                ++b;
            }
        }
    }
    forn(m1, 1<<P) {
        if (!br[0][m1]) {
            continue;
        }
        int r = gr[0][m1];
        int l = gl[0][m1];
        int s = l;
        while (1) {
            if (br[1][s]) {
                res += val(r & gr[1][s]);
            }
            if (s == 0) {
                break;
            }
            s = (s-1) & l;
        }
    }
}

void solve() {
    {
        Timer t("up");
        up();
    }
    {
        Timer t("go2");
        go2();
    }
    cout << res << endl;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
