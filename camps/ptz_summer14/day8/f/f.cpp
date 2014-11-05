#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
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

int n;
//int g[n], r[n], e[n], t[n];

typedef vector <vector <long long> > matrix;

const long long mod = 998244353;

matrix operator*(const matrix & l, const matrix & r) {
    
    int n = l.size();
    
    matrix res(n, vector <long long>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                res[i][j] = (res[i][j] + l[i][k] * r[k][j]) % mod;
            }
        }
    }
    return res;
}

matrix pw(matrix a, int n) {
    matrix res(a.size(), vector <long long>(a.size()));
    
    for (int i = 0; i < (int)a.size(); ++i) {
        res[i][i] = 1;
    }
    
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
    /*g[0] = 1;
    
    for (int i = 1; i < n; ++i) {
        g[i] = 1;
        for (int j = 0; j < i; ++j) {
            g[i] += r[j] + e[j];a
            r[i] += (1 << (i - j - 1)) * (2 * e[j] + g[j]);
            e[i] += t[j];
            t[i] += r[j] + 2 * e[j];
        }
        cout << g[i] << " ";
    }*/
    freopen("figure.in", "r", stdin);
    freopen("figure.out", "w", stdout);
    while (cin >> n) {
    if (!n) return 0;
    int m = 11;
    
    matrix A(m, vector <long long>(m));
    
    A[0][10] = 1;
    A[0][5] = 1;
    A[0][6] = 1;
    
    A[1][8] = 2;
    A[1][9] = 1;
    
    A[2][7] = 1;
    
    A[3][5] = 1;
    A[3][6] = 2;
    
    A[4][4] = 1;
    A[4][10] = 1;
    A[4][5] = 1;
    A[4][6] = 1;
    
    A[5][5] = 1;
    A[5][8] = 2;
    A[5][9] = 1;
    
    A[6][6] = 1;
    A[6][7] = 1;
    
    A[7][7] = 1;
    A[7][5] = 1;
    A[7][6] = 2;
    
    A[8][8] = 2;
    A[8][7] = 1;
    
    A[9][9] = 2;
    A[9][10] = 1;
    A[9][5] = 1;
    A[9][6] = 1;
    
    A[10][10] = 1;
    
    A = pw(A, n);
    
    long long res = A[0][0] + A[0][9] + A[0][10];
    
    res %= mod;
    
    cout << res << endl;
}
    
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
