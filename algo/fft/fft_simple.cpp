#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <complex>
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
const int inf = 1e9+100500;

typedef double ld;

typedef complex<ld> base;

int n, nb;

inline int rev(int x) {
    int y = 0;
    forn(i, nb) {
        y = (y<<1)^(x&1);
        x >>= 1;
    }
    return y;
}

base angles[1<<22];
base rangles[1<<22];

void gen_angles() {
    ld ang = 2 * M_PI / n;
    base w(cosl(ang), sinl(ang));
    forn(i, n + 1) {
        rangles[n-i] = angles[i] = base(cosl(ang * i), sinl(ang * i));
    }
}

void fft(base* a, bool rev) {
    forn(i, n) {
        int y = ::rev(i);
        if (i < y) {
            swap(a[i], a[y]);
        }
    }

    base *w;
    for (int len = 2; len <= n; len *= 2) {
        for (int i = 0; i < n; i += len) {
            w = (rev ? rangles : angles);
            for (int j = 0; j < len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * (*w);
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w += n / len;
                if (rev) {
                    a[i+j] /= 2;
                    a[i+j+len/2] /= 2;
                }
            }
        }
    }
//     forn(i, n) cout << a[i] << " ";
//     cout << endl;
}

const int maxn = 1<<22;
base ba[maxn], bb[maxn];
const int BASE = 10;
i64 a[maxn], b[maxn];
char buf[maxn];
int n1, n2;

int readnum(i64* dst) {
    scanf("%s", buf);
    char *s = buf;

    int n = strlen(buf);
    int k = 0;
    int pow = 1;
    ford(i, n) {
        if (pow == BASE) {
            ++k;
            pow = 1;
        }
        dst[k] += (s[i] - '0') * pow;
        pow *= 10;
    }
    return k + 1;
}

void print_num(i64* src, int k) {
//     forn(i, k) {
//         assert(src[i] >= 0);
//     }
    while (src[k-1] == 0 && k > 1) {
        --k;
    }
//     cout << "k = " << k << endl;
    printf("%d", (int)src[k-1]);
    ford(i, k-1) {
        printf("%01d", (int)src[i]);
    }
    printf("\n");
}

void scan() {
    n1 = readnum(a);
    n2 = readnum(b);
}

void multiply() {
    n = 1;
    nb = 0;
    while (n < n1 + n2 + 1) {
        n *= 2;
        ++nb;
    }
    gen_angles();
    forn(i, n1) {
        ba[i] = a[i];
    }
    fft(ba, 0);

    forn(i, n2) {
        bb[i] = b[i];
    }
    fft(bb, 0);

    forn(i, n) {
        ba[i] *= bb[i];
    }

    fft(ba, 1);

    ld mn = 0;
    forn(i, n) {
//         assert(ba[i].real() >= -1e-9);
//         assert(ba[i].real() + 0.5 > 0);
        mn = min(mn, ba[i].real());
        a[i] = (i64)(ba[i].real() + 0.5);
        assert(a[i] >= 0);
    }
    cerr << "mx error = " << mn << endl;
    int cr = 0;
    forn(i, n) {
        a[i] += cr;
        cr = a[i] / BASE;
        a[i] %= BASE;
    }
    assert(cr == 0);
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    cout.precision(2);
    cout << fixed;
    multiply();
//     print_num(a, n);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
