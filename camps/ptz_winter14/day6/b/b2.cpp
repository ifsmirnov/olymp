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
const int maxn = 2001;
typedef vector<vi> vvi;

const int base = 10000;
typedef vector<int> ml;
ml operator+(const ml& a, const ml& b) {
//     cerr << "a" << endl;
    ml c(max(a.size(), b.size()) + 1);
    int cr = 0;
    for(size_t i = 0; i < c.size(); ++i) {
        c[i] = cr + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
        cr = c[i] / base;
        c[i] %= base;
    }
    while (!c.empty() && !c.back()) c.pop_back();
//     cerr << "b" << endl;
    return c;
}
ml operator*(const ml& a, const ml& b) {
//     cerr << "A" << endl;
    ml c(a.size() + b.size() + 1);
    forn(i, a.size()) {
        int cr = 0;
        forn(j, b.size()) {
            c[i+j] += a[i] * b[j] + cr;
            cr = c[i+j] / base;
            c[i+j] %= base;
        }
        for (int j = b.size(); cr; ++j) {
            c[i+j] += cr;
            cr = c[i+j] / base;
            c[i+j] %= base;
        }
    }
    while (!c.empty() && !c.back()) c.pop_back();
//     cerr << "B" << endl;
    return c;
}
ml from_int(int x) {
    ml a;
    while (x) {
        a.pb(x%base);
        x /= base;
    }
    return a;
}
ml operator*(int x, const ml& a) {
    return from_int(x) * a;
}

void out(const ml& a) {
    if (a.empty()) {
        printf("0\n");
        return;
    }
    printf("%d", a.back());
    for (int i = (int)a.size()-2; i >= 0; --i)
        printf("%04d", a[i]);
    printf("\n");
}

#define swap sdkfj
ml dp[maxn][2 * maxn];
ml lazy[maxn];
int swap[maxn];

ml getdp(int i, int j) {
    //cerr << i << ' ' << j << '\n';
    //printf("%d %d\n", i, j);
    ml res;
    if (j <= 2 * i) {
        res = dp[i][j];
    } else {
        int k = (j - 2 * i + 1) / 2;
        //out(dp[i][j - 2 * k]);
        //printf("%d\n", 2 * k);
        //out(lazy[i]);
        res = dp[i][j - 2 * k] + from_int(2 * k) * lazy[i];
        //out(res);
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    int N;
    cin >> N;
    forn(i, N) {
        int x, y;
        cin >> x >> y;
        swap[N - i - 1] = x < y;
    }
    dp[0][0] = dp[0][1] = from_int(0);
    lazy[0] = ml(1,0);
    for (int i = 1; i <= N; ++i) {
        lazy[i] = from_int(2) * lazy[i - 1] + from_int(2);
    }
    //out(lazy[1]);
    
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= 2 * i; ++j) {
            //cerr << i << ' ' << j << '\n';
            if (j % 2 == swap[i - 1]) {
                dp[i][j] = getdp(i - 1, 2 * j) + from_int(2 * j);
            } else {
                dp[i][j] = min(getdp(i - 1, 2 * j + 2) + from_int(2 * j + 1), getdp(i - 1, 2 * j + 1) + from_int(2 * j + 2));
            }
            //printf("%d %d: ", i, j);
            //out(dp[i][j]);
        }
    }
    out(dp[N][1]);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
