#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
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
const int maxn = 1000500;

char buf[maxn];
char s[maxn];
int p[maxn];
int n, N;
int buflen;

int K;
int d[1<<(21+2)];

int pi(char* s, int n) {
    p[0] = 0;
    int mx = 0, mxp = 0;
    for (int i = 1; i < n; ++i) {
        p[i] = p[i-1];
        while (p[i] && s[p[i]] != s[i]) {
            p[i] = p[p[i]-1];
        }
        p[i] += s[i] == s[p[i]];
        if (p[i] > mx) {
            mx = p[i];
            mxp = i - p[i];
        }
    }
    return mxp;
}

void addchar() {
    int offset = N-n;
    if (n < buflen) {
        s[offset - 1] = buf[n];
    } else {
        int h = 1;
        bool ok = false;
        bool lastok = false;
        forn(i, min(K, n)) {
             h += h + s[offset + i] - '0';
             if (d[h]) {
                 s[offset - 1] = '1' ^ '0' ^ d[h];
                 ok = true;
                 lastok = true;
             } else {
                 lastok = false;
             }
        }
        if (lastok || !ok) {
            int pos = pi(s+offset, n);
            s[offset - 1] = '1' ^ '0' ^ s[pos+offset];
        }
    }

    // add hashes
    int h = 1;
    forn(i, min(K, n)) {
         h += h + s[offset + i] - '0';
         d[h] = s[offset - 1];
    }

    ++n;
}

void solve() {
    int n, k;
    scanf("%s%d%d", buf, &n, &k);
    buflen = strlen(buf);
    N = n+k-1;
    s[N] = '\0';

    K = 1;
    while ((1<<K) < N*2) ++K;

    forn(i, 1<<(K+2)) {
        d[i] = 0;
    }

    forn(i, N) s[i] = '.';
    ::n = 0;

    while (::n <= N) {
        addchar();
    }

    reverse(s, s+N);
    printf("%s\n", s + n - 1);
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    scanf("%d", &t);
    forn(i, t) {
        solve();
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
