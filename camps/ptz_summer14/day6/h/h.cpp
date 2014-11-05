#include <bits/stdc++.h>

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
typedef double ld;

ld fact[100000];
void build_fact() {
    fact[0] = fact[1] = 0;
    fore(i, 2, 99999)
        fact[i] = fact[i - 1] + logl((ld)i);
}

int n, m;
int x, y;
int p;
double pr;
double logp, lognp;


ld cnk(int n, int k) {
    return fact[n] - fact[k] - fact[n-k];
}

ld getM(int x, int y, int xs, int ys) {
    int dx = n * x - xs;
    int dy = m * y - ys;
    if (dx < 0 || dy < 0) return 0;
    return (dx + dy) * exp(
        cnk(dx+dy, dy) +
        dx * logp +
        dy * lognp);
}

ld subm[500][500];
ld s[500][500];

void fill_prematrix() {
    vector<pii> t;
    forn(i, 201) forn(j, 201) t.pb(mp(i, j));
    sort(all(t), [](const pii& a, const pii& b) {
        auto f = [](const pii& t) -> double { return pr * t.se + (1.0-pr) * t.fi; };
        return f(a) < f(b);
    });
    const int K = 200;
    t.resize(K);
//     for (auto p: t) {
//         cout << "tower " << p.fi << " " << p.se << endl;
//     }
    forn(x, n) forn(y, m) {
//         for (auto p: t) s[p.fi][p.se] = 0;
        subm[x][y] = 0;
//         subm[x][y] = getM(1, 1, x, y);
        for (auto p: t) {
//             int px = p.x;
//             int py = p.y;
            subm[x][y] += getM(p.fi, p.se, x, y);
//             break;
        }
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    build_fact();

    scanf("%d%d%d%d%d", &n, &m, &x, &y, &p);

    pr = (double)p / 100;
    logp = logl(pr);
    lognp = logl(1.0-pr);

    double dp[n][m];

    memset(dp, 0, sizeof(dp));

    int it = 2000;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i || j) {
                dp[i][j] = n * m;
            }
        }
    }

    while (it--) {
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                if (i || j) {
                    int a = i + 1;
                    int b = j;
                    if (a == n) {
                        a = 0;
                    }
                    dp[i][j] = 1 + pr * dp[a][b];
                    a = i;
                    b = j + 1;
                    if (b >= m) {
                        b = 0;
                    }
                    dp[i][j] += (1 - pr) * dp[a][b];
                }
            }
        }
    }

    cout.precision(2);
    cout << fixed;
    forn(i, n) {
        forn(j, m) cout << dp[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << endl;
    cout << setprecision(10) << fixed;
    cout << dp[x % n][y % m] << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
