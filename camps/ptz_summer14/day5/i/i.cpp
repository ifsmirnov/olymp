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

int mod = 119;

typedef vector <int> poly;

int p;
int q;
int a;
int b;

poly operator*(const poly & A, const poly & B) {
    poly res(A.size() + B.size());
    for (int i = 0; i < (int)A.size(); ++i) {
        for (int j = 0; j < (int)B.size(); ++j) {
            res[i + j] += A[i] * B[j];
            if (res[i + j] >= mod) {
                res[i + j] %= mod;
            }
        }
    }
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

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    int n;
    
    cin >> n >> a >> b >> p >> q;
    
    
    a %= mod;
    b %= mod;
    
    poly d(2);
    d[1] = 1;
    
    d = pw(d, n + q - 1);
    
    int ans = accumulate(all(d), 0);
    ans %= mod;
    cout << ans << endl;
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
