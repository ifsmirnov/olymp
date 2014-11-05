#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <cmath>
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
typedef long double ld;
const int inf = 1e9+100500;
const int maxn = 100500;

const i64 p[2] = {1000000000 + 7, 1000000000 + 9};
i64 fib[2][100];
ld fibd[100];

i64 euclid(i64 A, i64 B, i64 &x, i64 &y) {
    if (B == 0) {
        x = 1;
        y = 0;
        return A;
    }
    i64 X, Y;
    i64 res = euclid(B, A % B, X, Y);
    x = Y;
    y = X - Y * (A / B);
    return res;
}

i64 inv(i64 A, i64 Q) {
    i64 x, y;
    euclid(A, Q, x, y);
    return (x % Q + Q) % Q;
}

i64 norm(i64 A, i64 Q) {
    return (A % Q + Q) % Q;
}

pair<i64, i64> solve(i64 A, i64 B, i64 C, i64 D, i64 E, i64 F, i64 Q) {
    i64 delta = norm(A * E - B * D, Q);
    if (delta == 0) {
        return mp(-1, -1);
    }
    delta = inv(delta, Q);
    i64 dx = norm(C * E - B * F, Q), dy = norm(A * F - D * E, Q);
    return mp(norm(dx * delta, Q), norm(dy * delta, Q));
}

i64 mul(i64 A, i64 B, i64 P) {
    i64 res = 0;
    while (B) {
        if (B & 1) {
            res += A;
            if (res >= P) {
                res -= P;
            }
        }
        A += A;
        if (A >= P) {
            A -= P;
        }
        B >>= 1;
    }
    return res;
}

i64 kto(i64 x1, i64 x2, i64 p1, i64 p2) {
    i64 ip2 = inv(p2 % p1, p1), ip1 = inv(p1 % p2, p2);
    i64 Q = p1 * p2;
    return (mul(mul(x1, ip2, Q), p2, Q) + mul(mul(x2, ip1, Q), p1, Q)) % Q;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio(false);
    long long R, S;
    forn(i, 2) {
        forn(j, 2) {
            fib[i][j] = j ? 0 : 1;
          //  cerr << fib[i][j] << ' ';
        }
        //cerr << '\n';
        fibd[i] = i ? 0 : 1;
    }
    for (int i = 2; i < 100; ++i) {
        forn(j, 2) {
            fib[j][i] = (fib[j][i - 1] + fib[j][i - 2]) % p[j];
          //  cerr << fib[j][i] << ' ';
        }
        //cerr << '\n';
        fibd[i] = fibd[i - 1] + fibd[i - 2];
    }
    int T;
    cin >> T;
    
    while (T-->0) {
        cin >> R >> S;
        pair<i64, i64> ans = mp(R, S);
        for (int i = 0; i + 1 < 100; ++i) {
            for (int j = i + 1; j + 1 < 100; ++j) {
                pair<i64, i64> A[2];
                forn(k, 2) {
                    A[k] = solve(fib[k][i], fib[k][i + 1], R % p[k], fib[k][j], fib[k][j + 1], S % p[k], p[k]);
                }
                pair<i64, i64> B = mp(kto(A[0].first, A[1].first, p[0], p[1]), kto(A[0].second, A[1].second, p[0], p[1]));
                bool ok = true;
                ok &= (fabs((fibd[i] * B.first + fibd[i + 1] * B.second) / R - 1.0) < 1e-7);
                ok &= (fabs((fibd[j] * B.first + fibd[j + 1] * B.second) / S - 1.0) < 1e-7);
                if (ok) {
                    ans = min(ans, B);
                }
            }
        }
        cout << ans.first << ' ' << ans.second << '\n';
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
