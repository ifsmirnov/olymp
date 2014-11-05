#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstring>
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

const int maxn = 28;

i64 mul(i64 a, i64 b) {
    if ((double)a*b > 2e18) {
        return -1;
    }
    i64 t = a * b;
    if (t > 1000000000000000000ll) {
        return -1;
    }
    return t;
}

i64 add(i64 a, i64 b) {
    i64 t = a + b;
    if (t > 1000000000000000000ll) {
        return -1;
    }
    return t;
}

i64 cnk[maxn][maxn];
void compc() {
    cnk[0][0] = 1;
    fore(n, 1, maxn-1) {
        cnk[n][0] = cnk[n][n] = 1;
        fore(k, 1, n-1) {
            cnk[n][k] = cnk[n-1][k] + cnk[n-1][k-1];
        }
    }
}

int n, m, k, b;
int bound[maxn], bc[maxn];
int numc[maxn];
int numc_real[maxn];
int mapc[maxn];
char buf[maxn];
int diff_chars;

bool scan() {
    memset(numc, 0, sizeof numc);
    memset(mapc, 0, sizeof mapc);
    memset(numc_real, 0, sizeof numc_real);

    scanf("%d%d", &n, &m);
    if (n == 0) {
        return false;
    }
    k = n*m;

    forn(i, m) {
        scanf("%d%s", &bound[i], buf);
        bc[i] = buf[0]-'a';
    }

    forn(i, n) {
        scanf("%s", buf + m*i);
    }
    forn(i, k) {
        numc_real[buf[i]-'a']++;
    }
    return true;
}

void make_mapc() {
    sort(buf, buf+k, [](int a, int b) {
        bool a_in = false, b_in = false;
        forn(i, m) if (bc[i] == b-'a') b_in = true;
        forn(i, m) if (bc[i] == a-'a') a_in = true;
        if (a_in ^ b_in) {
            return a_in;
        } else {
            return a < b;
        }
    });
    diff_chars = unique(buf, buf+k) - buf;
    buf[diff_chars] = '\0';
    cout << "diff_chars= " << diff_chars << endl;

    b = 0;
    while (1) {
        bool ok = false;
        forn(i, m) {
            if (bc[i] == buf[b] - 'a') {
                ok = true;
                break;
            }
        }
        if (!ok) break;
        else ++b;
    }
    cout << "num_bounds = " << b << endl;

    forn(i, diff_chars) {
        mapc[buf[i]-'a'] = min(b, i);
        numc[mapc[buf[i]-'a']] += numc_real[buf[i]-'a'];
    }

    cout << "buf: " << buf << endl;

    forn(i, m) {
        bc[i] = mapc[bc[i]];
    }

    cout << "bounds:" << endl;
    forn(i, m) cout << bound[i] << " for char " << bc[i] << endl;
    cout << endl;
    cout << "numc-s: ";
    forn(i, b+1) cout << numc[i] << " "; cout << endl;
}

i64 solve() {
    make_mapc();
    cout << buf << endl;

    return 1;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    compc();

    for (int i = 1; scan(); ++i) {
        i64 res = solve();
        (void)res; // print res
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
