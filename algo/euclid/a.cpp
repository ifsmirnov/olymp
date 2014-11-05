#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int n = 1000000;

class Timer {
public:
    Timer(string s = "") : s(s), t(clock()) {}
    ~Timer() {
        cout << "Time [" << s << "]: " << (clock() - t) / 1000 << " ms" << endl;
    }

    string s;
    time_t t;
};

int a[n];

void gen() {
    Timer timer("gen");
    for (int i = 0; i < n; ++i) {
        a[i] = rand();
    }
}

int n_iter = 0;

void test(string name, function<int(int,int)> gcd) {
    n_iter = 0;
    Timer timer(name);
    int res = 0;
    for (int i = 0; i < n-1; ++i) res += gcd(a[i], a[i+1]);
    if (res != 13290407) {
        cerr << "Error" << endl;
    }
    if (n_iter != 0) {
        cout << "n_iter = " << n_iter << endl;
    }
//     cerr << "res = " << res << endl;
}

int gcd_rec(int a, int b) {
    if (b) return gcd_rec(b, a%b);
    else return a;
}

int gcd_nrec(int a, int b) {
    while (b) {
        ++n_iter;
        a %= b;
        swap(a, b);
    }
    return a;
}

int gcd_gcc(int a, int b) {
    return __gcd(a, b);
}

int gcd_bin(int a, int b) {
    int res = 1;
    while (a&&b) {
        while (!((a|b)&1)) a>>=1,b>>=1,res<<=1;
        while (!(a&1)) a>>=1;
        while (!(b&1)) b>>=1;
        if (a<b) b -= a;
        else a -= b;
    }
    return res * (a+b);
}

int gcd_noswap(int a, int b) {
    while (a&&b) {
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}

int gcd_fast(int a, int b) {
    while (b) {
        ++n_iter;
        a %= b;
        if (a*2 > b) a = b-a;
        swap(a, b);
    }
    return a;
}

int gcd_fast_first_swap(int a, int b) {
    if (a < b) swap(a, b);
    while (b) {
        ++n_iter;
        a %= b;
        if (a*2 > b) a = b-a;
        swap(a, b);
    }
    return a;
}

int gcd_bin_wiki(int u, int v)
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd_bin_wiki(u >> 1, v);
        else // both u and v are even
            return gcd_bin_wiki(u >> 1, v >> 1) << 1;
    }

    if (~v & 1) // u is odd, v is even
        return gcd_bin_wiki(u, v >> 1);

    // reduce larger argument
    if (u > v)
        return gcd_bin_wiki((u - v) >> 1, v);

    return gcd_bin_wiki((v - u) >> 1, u);
}

int gcd_bin_wiki_fast(int u, int v) {
    int shift;

    /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
    if (u == 0) return v;
    if (v == 0) return u;

    /* Let shift := lg K, where K is the greatest power of 2
       dividing both u and v. */
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while ((u & 1) == 0)
        u >>= 1;

    /* From here on, u is always odd. */
    do {
        /* remove all factors of 2 in v -- they are not common */
        /*   note: v is not zero, so while will terminate */
        while ((v & 1) == 0)  /* Loop X */
            v >>= 1;

        /* Now u and v are both odd. Swap if necessary so u <= v,
           then set v = v - u (which is even). For bignums, the
           swapping is just pointer movement, and the subtraction
           can be done in-place. */
        if (u > v) {
            unsigned int t = v; v = u; u = t;}  // Swap u and v.
        v = v - u;                       // Here v >= u.
    } while (v != 0);

    /* restore common factors of 2 */
    return u << shift;
}

int gcd_evg(int u, int v)
{
    if (!u || !v) {
        return u | v;
    }

    int shift = __builtin_ctz(u | v);
    u >>= shift;
    v >>= shift;

    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) swap(u, v);
        v -= u;
    } while (v);
    return u << shift;
}

int main() {
    gen();
//     test("rec", gcd_rec);
    test("nrec", gcd_nrec);
//     test("__", gcd_gcc);
//     test("bin", gcd_bin);
//     test("noswap", gcd_noswap);
    test("fast", gcd_fast);
    test("fast_swap", gcd_fast_first_swap);
    test("gcd_bin_wiki", gcd_bin_wiki);
    test("gcd_bin_wiki_fast", gcd_bin_wiki_fast);
    test("gcd_evg", gcd_evg);
}


