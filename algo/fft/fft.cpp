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

void fft(base* a, bool rev) {
    // butterfly
    forn(i, n) {
        int y = ::rev(i);
        if (i < y) {
            swap(a[i], a[y]);
        }
    }

    for (int len = 2; len <= n; len *= 2) {
        ld ang = 2 * M_PI / len;
        if (rev) {
            ang = -ang;
        }
        base wlen(cosl(ang), sinl(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
                if (rev) {
                    a[i+j] /= 2;
                    a[i+j+len/2] /= 2;
                }
            }
        }
    }
}

const int maxn = 1<<10;
base ba[maxn], bb[maxn];
const int BASE = 10000;
int a[maxn], b[maxn];
char buf[maxn];
int n1, n2;

int readnum(int* dst) {
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

void print_num(int* src, int k) {
    while (src[k-1] == 0 && k > 1) {
        --k;
    }
//     cout << "k = " << k << endl;
    printf("%d", src[k-1]);
    ford(i, k-1) {
        printf("%04d", src[i]);
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

//     cout << "n = " << n << endl;

    forn(i, n1) {
        ba[i] = a[i];
    }
//     forn(i, n) cout << ba[i] << " "; cout << endl;
    fft(ba, 0);
//     forn(i, n) cout << ba[i] << " "; cout << endl;
//     cout << endl;

    forn(i, n2) {
        bb[i] = b[i];
    }
    fft(bb, 0);
//     forn(i, n) cout << bb[i] << " "; cout << endl;
//     cout << endl;

    forn(i, n) {
        ba[i] *= bb[i];
    }
//     forn(i, n) cout << ba[i] << " "; cout << endl;
//     cout << endl;

    fft(ba, 1);
//     forn(i, n) cout << ba[i] << " "; cout << endl;
//     cout << endl;

    forn(i, n) {
        a[i] = (int)(ba[i].real() + 0.5);
    }
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

//     n = 8;
//     nb = 3;
// 
//     base a[8] = {1,7,2,9,0,0,0,0};
//     fft(a, 0);
//     forn(i, n) {
//         cout << a[i] << endl;
//     }
//     cout << endl;
//     forn(i, 8) {
//         a[i] *= a[i];
//     }
//     fft(a, 1);
//     cout.precision(3);
//     cout << fixed;
//     forn(i, n) {
//         cout << a[i] << " ";
//     }
//     cout << endl;

    scan();
    multiply();
    print_num(a, n);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
