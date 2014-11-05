#include <iostream>
#include <cstdio>
#include <cstring>
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
const int maxn = 1000500;

// #warning
const int sz = 40 * 10;
int ctag = 0;
short tag[sz];
i64 ht[sz];
char hval[sz];
void init() {
    ++ctag;
}
// int cnt = 0;
inline int mhash(i64 x) {
    x = abs((x*x + x) ^ (5 * x));
    return x % sz;
}
inline char& hget(i64 x) {
    int i = mhash(x);
    while (ht[i] != x && tag[i] == ctag) {
        ++i;
        if (i == sz) i = 0;
    }
    if (tag[i] != ctag) {
//         ++cnt;
        ht[i] = x;
        tag[i] = ctag;
        hval[i] = 2;
    }
    return hval[i];
}

int z[maxn];

int zmagic(char *s, int N) {
    z[0] = 0;
    int m = 0, l = 0, r = 0;
    for (int i = 1; i < N; ++i) {
        z[i] = 0;
        if (i > r) {
            l = r = i;
        }
        z[i] = min(z[i - l], r - i);
        while (i + z[i] < N && s[i + z[i]] == s[z[i]]) {
            ++z[i];
            l = i;
            r = i + z[i];
        }
        if (z[i] > z[m]) {
            m = i;
        }
    }
    return m-1;
}

vi pi(const string& s) {
    vi p(s.size());
    p[0] = 0;
    for (int i = 1; i < (int)s.length(); ++i) {
        p[i] = p[i-1];
        while (p[i] && s[i] != s[p[i]]) {
            p[i] = p[p[i]-1];
        }
        p[i] += s[i] == s[p[i]];
    }
    return p;
}

int substr(const string& s, const string& t) {
    ford(i, (int)s.length() - (int)t.length()) {
        bool ok = true;
        forn(j, t.length()) {
            if (s[i+j] != t[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return i;
        }
    }
    return -1;
}

const i64 base = 10099;

int n;
char s[1000500];

int tg = 0;
char nc[1<<26];
short used[1<<26];

vector<int> hi;

void setInitHashes() {
    ++tg;
    forn(i, n-1) {
        int h = 1;
        for (int j = i; j >= 0 && i-j <= 22; --j) {
            h = h*2 + s[j] - '0';
            used[h] = tg;
            nc[h] = s[i+1];
        }
    }
}

char zz[maxn];
void inc2000() {
    forn(i, n) zz[i] = s[n-i-1];
    int t = zmagic(zz, n);
//     cerr << t << endl;
    char res;
    if (t == -1) {
        res = s[n-1];
    } else {
        res = s[n-t-1];
    }
    s[n++] = '1'^'0'^res;
    s[n] = '\0';
}

void inc() {
    const int K = 3010;
    if (n < K) {
        inc2000();
        return;
    } else if (n == K) {
        setInitHashes();
//         cerr << "sdfds" << endl;
    }
    int th = 22;

    // build hi
    {
        hi.clear();
        int i = n-1;
        int h = 1;
        for (int j = i; i-j <= th; --j) {
            h = h * 2 + s[j] - '0';
            hi.pb(h);
        }
    }

    // find next char
    bool fit = false;
    for (int i = hi.size() - 1; i >= 0; --i) {
        int h = hi[i];
        if (used[h] == tg) {
            s[n] = '1'^'0'^nc[h];
            fit = true;
            break;
        }
    }
    if (!fit) {
//         cerr << n << endl;
        s[n] = '1'^'0'^s[n-1];
    }

    // fill prev
    forn(i, hi.size()) {
        used[hi[i]] = tg;
        nc[hi[i]] = s[n];
    }

    ++n;
    s[n] = '\0';
}

void solve() {
    cin >> s;
    int N, k;
    cin >> N >> k;
    n = strlen(s);

    while (n < N+k-1) {
        inc();
    }

//     cerr << "cnt = " << cnt << endl;

    printf("%s\n", s + n - k);
}

vector<int> lens;

void addc(string& s) {
    int n = s.length();
    for (int t = s.length(); t  > 0; --t) {
        int pos = substr(s, s.substr(n-t, t));
        if (pos != -1) {
            lens.pb(t);
            s += '1'^'0'^s[pos+t];
            return;
        }
    }
    s += '1'^'0'^s[s.length() - 1];
}

// void solve() {
//     string s;
//     int n, k;
//     cin >> s >> n >> k;
//     while ((int)s.length() < n+k-1) {
//         addc(s);
//     }
// //     cout << s << endl;
//     cout << s.substr(s.length() - k, k) << endl;
// }

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t;
    cin >> t;
    forn(i, t) {
        solve();
    }

//     forn(i, lens.size()) {
//         cout << lens[i] << " ";
//     }
//     cout << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
