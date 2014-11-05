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
typedef double lf;
typedef unsigned long long u64;
const int inf = 1e9+100500;

int mod = 119;

typedef vector <int> poly;

int p;
int q;
int a;
int b;
int sz;

struct cnum
{
    lf re, im;

    cnum(lf nre = 0, lf nim = 0): re(nre), im(nim) {}

    cnum operator + (const cnum &c) const
    {
        return cnum(re + c.re, im + c.im);
    }

    cnum operator - (const cnum &c) const
    {
        return cnum(re - c.re, im - c.im);
    }

    cnum operator * (const cnum &c) const
    {
        return cnum(re * c.re - im * c.im, re * c.im + im * c.re);
    }

    cnum operator /= (const lf k)
    {
        re /= k;
        im /= k;
        return *this;
    }
};

const lf pi = acosl(-1.0);
int rbits[1 << 15];
cnum roots[1 << 15];

void precalc()
{
    int logsz = 0;
    for (int x = 1; x < sz; x *= 2) ++logsz;
    for (int i = 0; i < sz; ++i)
    {
        roots[i] = cnum(cosl(2 * pi * i / sz), sinl(2 * pi * i / sz));
//         cout << roots[i].re << " " << roots[i].im << endl;
    }
    for (int i = 0; i < sz; ++i)
    {
        rbits[i] = 0;
        for (int j = i, s = 0; s < logsz; ++s, j >>= 1)
            rbits[i] = (rbits[i] << 1) | (j & 1);
    }
}

void fft(vector<cnum> &v, bool rev)
{
    // reverse bits
    assert((int) v.size() == sz);
    int n = sz;
    for (int i = 0; i < n; ++i)
        if (i < rbits[i])
            swap(v[i], v[rbits[i]]);

//     cout << "LETS FFT!!!" << endl;
//     if (rev)
//     {
//         for (int i = 0; i < sz; ++i)
//             cout << v[i].re << " " << v[i].im << endl;
//         cout << "-------------------" << endl;
//     }
    // fft
    for (int l = 2; l <= n; l *= 2)
    {
        for (int j = 0; j < n; j += l)
        {
            int cur = 0, step = rev ? -(n / l) : n / l;
            for (int i = 0; i < l / 2; ++i)
            {
                cnum a = v[i + j], b = v[i + j + l / 2] * roots[cur];
                v[i + j] = a + b;
                v[i + j + l / 2] = a - b;
                cur += step;
                if (cur < 0) cur += n;
            }
        }
//         if (rev)
//         {
//             for (int i = 0; i < sz; ++i)
//                 cout << v[i].re << " " << v[i].im << endl;
//             cout << "-------------------" << endl;
//         }
    }
    if (rev)
        for (int i = 0; i < n; ++i)
            v[i] /= n;
}

poly operator*(const poly & A, const poly & B) {
    vector<cnum> v1(sz), v2(sz);
    for (size_t i = 0; i < A.size(); ++i) v1[i] = A[i];
    for (size_t i = 0; i < B.size(); ++i) v2[i] = B[i];

    fft(v1, false);
    fft(v2, false);
    for (int i = 0; i < sz; ++i)
        v1[i] = v1[i] * v2[i];
    fft(v1, true);

    poly res(sz);
    for (int i = 0; i < sz; ++i)
        res[i] = (int) (v1[i].re + 0.5) % mod;

//     poly res(A.size() + B.size());
//     for (int i = 0; i < (int)A.size(); ++i) {
//         for (int j = 0; j < (int)B.size(); ++j) {
//             res[i + j] += A[i] * B[j];
//             if (res[i + j] >= mod) {
//                 res[i + j] %= mod;
//             }
//         }
//     }
    for (int i = res.size() - 1; i >= q; --i) {
        res[i - p] = (res[i - p] + a * res[i]) % mod;
        res[i - q] = (res[i - q] + b * res[i]) % mod;
    }
    res.resize(q);
    return res;
}

poly pw(poly a, int n) {
    poly res(1, 1);
    while (n) {
        if (n & 1) {
            res = res * a;
        }
        a = a * a;
        n >>= 1;
    }
    return res;
}

void test()
{
    sz = 4;
    precalc();
    for (int i = 0; i < sz; ++i) cout << rbits[i] << " ";
    cout << endl;
    vector<cnum> v({cnum(0), cnum(0), cnum(1), cnum(0)});
    fft(v, false);
    exit(0);
}

int main() {
#ifdef HOME
//     test();
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n >> a >> b >> p >> q;
    sz = 1;
    while (sz < 2 * q) sz *= 2;
    precalc();

    a %= mod;
    b %= mod;

    poly d(2);
    d[1] = 1;

//     d = d * d;
    d = pw(d, n + q - 1);

    int ans = accumulate(all(d), 0);
    ans %= mod;
    cout << ans << endl;
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
