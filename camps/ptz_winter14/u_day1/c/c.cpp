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

char s[101][101];
int dp[101][11][1 << 10][22];

const int P = 1000000000 + 7;

void add(int &x, int &y) {
    x += y;
    if (x >= P) {
        x -= P;
    }
}

int N, M, C, D;
int blocked(int x, int y) {
    if (x >= N) return 0;
    return s[x][y] == '0';
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    while (scanf("%d%d%d%d", &N, &M, &C, &D) > 0) {
        forn(i, N) {
            scanf("%s", s[i]);
        }
        forn(i, N + 1) {
            forn(j, M + 1) {
                forn(m, 1 << M) {
                    forn(q, 22) {
                        dp[i][j][m][q] = 0;
                    }
                }
            }
        }
        int initM = 0;
        forn(i, M) initM += (blocked(0, i) << i);
        dp[0][0][initM][0] = 1;
        forn(i, N) {
            forn(j, M) {
                forn(m, 1 << M) {
                    forn(q, 22) {
                        if (m & 1) {
                            add(dp[i][j + 1][(m + (blocked(i + 1, j) << M)) >> 1][q], dp[i][j][m][q]);
                            continue;
                        }
                        if (((m & 3) == 0) && j + 1 < M) {
                            add(dp[i][j + 1][(m + 3 + (blocked(i + 1, j) << M)) >> 1][q], dp[i][j][m][q]);
                        }
                        if (!blocked(i + 1, j)) {
                            add(dp[i][j + 1][(m + (1 << M)) >> 1][q], dp[i][j][m][q]);
                        }
                        add(dp[i][j + 1][(m + (blocked(i + 1, j) << M))>> 1][min(q + 1, 21)], dp[i][j][m][q]);
                    }
                }
            }
            forn(m, 1 << M) {
                forn(q, 22) {
                    dp[i + 1][0][m][q] = dp[i][M][m][q];
                }
            }
        }
        int ans = 0;
        for (int i = C; i <= D; ++i) {
            add(ans, dp[N][0][0][i]);
        }
        cout << ans << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
