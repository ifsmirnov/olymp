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
typedef long double ld;

int n, a, b;
long long c[55][55];
long double p, dp[55][55][55], f[55];

long double sumg(long double x, int N=0)
{
	return 1 / (1 - x);
	return ((long double)1.0 - powl(x, (long double)N)) / ((long double)1.0 - x);
}

int emul(int n, int a, int b, ld p) {
    i64 m = 0;
    i64 mm = (1ll<<n)-1;
    int c = 0;
    while (mm != m) {
        ++c;
        i64 cm = 0;
        int r = rand()%(b-a+1) + a;
        forn(i, r) {
            if (cm == mm) break;
            int j;
            do {
                j = rand()%n;
            } while (cm&(1ll<<j));
            m |= 1ll<<j;
            if (rand() < RAND_MAX * p) {
                cm |= 1ll<<j;
            }
        }
    }
    return c;
}

ld monte(int n, int a, int b, ld p, int iter) {
    ld s = 0;
    forn(I, iter) {
        s += emul(n, a, b, p);
    }
    return s / iter;
}

class cmp {
public: bool operator()(ld a, ld b) { return abs(a) > abs(b); }
};

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

	cin >> n >> a >> b >> p;
	for (int L = 0; L <= 50; L++)
		for (int N = 0; N <= n; N++)
			for (int K = 0; K <= N; K++) {
				if (L == 0 || N == 0) dp[L][N][K] = 1.0;
                else {
                    dp[L][N][K] = p * dp[L-1][N-1][K] + (1-p) * dp[L-1][N][K];
                    dp[L][N][K] *= (ld)(N-K)/N;
                }
            }
	f[0] = 1.0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = a; j <= b; j++)
			f[i] += dp[j][n][i];
		f[i] /= (long double)(b - a + 1);
        assert(f[i] < 1);
	}
	
	for (int i = 0; i <= n; i++)
		c[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	
	ld pn = 0;
    priority_queue<ld, vector<ld>, cmp> a;
	for (int i = 1; i <= n; i++) {
        if (i&1) a.push(c[n][i] * sumg(f[i]));
        else a.push(-c[n][i] * sumg(f[i]));
// 		if (i & 1) pn += (long double)c[n][i] * sumg(f[i]);
// 		else pn -= (long double)c[n][i] * sumg(f[i]);
    }

    while (a.size() > 1u) {
        ld x = a.top(); a.pop();
        ld y = a.top(); a.pop();
        cout << x << " " << y << endl;
        a.push(x+y);
    }
    pn = a.top();

//     assert(abs(monte(n, a, b, p, 10000) - pn) < 1);
	cout.precision(12); cout << fixed << pn << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
