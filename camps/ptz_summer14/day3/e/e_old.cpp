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
const int maxn = 1010;

int n, m, k;
int a[maxn][maxn];
char buf[maxn];

typedef int arr[maxn][maxn];
arr s;
arr typer, typeu, limr, limu, hr, hu, br, bu;
arr h, b;

void out(arr a) {
    forn(i, n) {
        forn(j, m) {
            if (inf == a[i][j] || a[i][j] == -1) cout << ". ";
            else cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void scan() {
    scanf("%d%d%d", &n, &m, &k);
    forn(i, n) {
        scanf("%s", buf);
        forn(j, m) a[i][j] = buf[j]-'0';
    }
}

int gets(int x1, int y1, int x2, int y2) {
    int res = s[x2][y2];
    if (x1) res -= s[x1-1][y2];
    if (y1) res -= s[x2][y1-1];
    if (x1&&y1) res += s[x1-1][y1-1];
    return res;
}

void transpose(arr a) {
    forn(i, max(n, m)) forn(j, i) swap(a[i][j], a[j][i]);
}

void fillLim(arr a, arr typer, arr limr, arr hr, arr br) {
    // limr
    forn(i, n) {
        queue<int> q;
        q.push(-1);
        int lastb = -1;
        forn(j, m) {
            if (a[i][j] == 1) {
                if (lastb == -1) {
                    lastb = j;
                }
                q.push(j);
                while ((int)q.size() > k + 1) {
                    q.pop();
                }
                if (j - lastb + 1 >= k + 1) {
                    typer[i][j] = 0;
                    limr[i][j] = j - lastb + 1;
                } else if ((int)q.size() == k + 1) {
                    typer[i][j] = 1;
                    limr[i][j] = j - q.front();
                } else {
                    typer[i][j] = -1;
                    limr[i][j] = -1;
                }
            } else {
                lastb = -1;
                if ((int)q.size() == k + 1) {
                    typer[i][j] = 1;
                    limr[i][j] = j - q.front();
                } else {
                    typer[i][j] = -1;
                    limr[i][j] = -1;
                }
            }
        }
    }

    // hr, br
    forn(j, m) {
        forn(i, n) {
            int x = 0;
            int mn = 100000;
            while (x <= i) {
                mn = min(mn, limr[i-x][j]);
                if (x >= mn) break;
                ++x;
            }
            hr[i][j] = x;
        }

        queue<int> q;
        forn(i, n) {
            if (typer[i][j] == 0) {
                q.push(i);
                if ((int)q.size() > k) {
                    q.pop();
                }
            }
            if ((int)q.size() == k) {
                br[i][j] = i - q.front() + 1;
            } else {
                br[i][j] = inf;
            }
        }

        while (!q.empty()) q.pop();
        forn(i, n) {
            if (typer[i][j] == 0) {
                q.push(i);
                if ((int)q.size() > k + 1) {
                    q.pop();
                }
            }
            if ((int)q.size() == k + 1) {
                hr[i][j] = min(hr[i][j], i - q.front());
            }
        }
    }
}

void fillArrays() {
    // s
    forn(i, n) forn(j, m) {
        s[i][j] = a[i][j];
        if (i) s[i][j] += s[i-1][j];
        if (j) s[i][j] += s[i][j-1];
        if (i&&j) s[i][j] -= s[i-1][j-1];
    }

    fillLim(a, typer, limr, hr, br);

    transpose(a);
    swap(n, m);
    fillLim(a, typeu, limu, hu, bu);
    transpose(a);
    transpose(typeu);
    transpose(limu);
    transpose(hu);
    transpose(bu);
    swap(n, m);

    forn(i, n) forn(j, m) h[i][j] = min(hr[i][j], hu[i][j]);
    forn(i, n) forn(j, m) b[i][j] = max(br[i][j], bu[i][j]);
    forn(i, n) forn(j, m) b[i][j] = max(b[i][j], k+1);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    fillArrays();
    out(a);
    out(typer);
    out(limr);
    out(hr);
    out(br);
    cout << endl;
    out(a);
    out(typeu);
    out(limu);
    out(hu);
    out(bu);
    cout << endl;
    cout << endl;
    out(a);
    out(h);
    out(b);
    cout << endl;

    i64 res = 0;
    forn(i, n-k+1) forn(j, m-k+1) {
        res += gets(i, j, i+k-1, j+k-1) == k*k;
    }
    forn(i, n) forn(j, m) if (h[i][j] >= b[i][j]) res += h[i][j] - b[i][j] + 1;
    cout << res << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
