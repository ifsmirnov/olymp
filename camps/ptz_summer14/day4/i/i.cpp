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
typedef unsigned long long u64;
const int inf = 1e9+100500;

u64 to[256];

u64 cloned[256];

u64 c1 = 0x5555555555555555ull;

u64 c2 = 0x3333333333333333ull;

u64 c4 = 0x0f0f0f0f0f0f0f0full;


u64 tr(u64 x) {
    u64 res = 0;
    for (int i = 0; i < 8; ++i) {
        res ^= (to[x & 255ull] << i);
        x >>= 8;
    }
    return res;
}

u64 mul(u64 a, u64 b) {
    b = tr(b);
    u64 res = 0;
    for (int i = 0; i < 8; ++i) {
        u64 d = cloned[b & 255ull] & a;
        d = (d & c1) ^ ((d >> 1ull) & c1);
        d = (d & c2) ^ ((d >> 2ull) & c2);
        d = (d & c4) ^ ((d >> 4ull) & c4);
        res ^= (d << i);
        b >>= 8;
    }
    return res;
}

u64 m2(u64 a, u64 b) {
    u64 res = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int k = 0; k < 8; ++k) {
                int p1 = i * 8 + k;
                int p2 = k * 8 + j;
                int p3 = i * 8 + j;
                res ^= (((a >> p1) & 1ull) & ((b >> p2) & 1ull)) << p3;
            }
        }
    }
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    for (int i = 0; i < 256; ++i) {
        to[i] = 0;
        cloned[i] = 0;
        for (int j = 0; j < 8; ++j) {
            if ((i >> j) & 1) {
                to[i] ^= 1ull << (8ull * j);
            }
            cloned[i] ^= (((u64)i) << (8ull * j));
        }
    }
    
    int n;
    
    u64 x, p, q;
    
    cin >> n >> x >> p >> q;
    
    u64 ans = 0;
    
    //u64 d = ULLONG_MAX;
    
    //cout << mul(d, d) << endl;
    
    
    while (n--) {
        x = x * p + q;
        u64 l = x;
        x = x * p + q;
        u64 r = x;
        ans ^= mul(l, r);
    }    
    cout << ans << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
