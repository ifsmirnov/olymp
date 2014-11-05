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

typedef vector <vector <unsigned> > matr;

matr operator*(const matr & a, const matr & b) {
    matr res(2, vector <unsigned>(2));
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return res;
}

const int N = 100;

matr D[N];

unsigned s;

unsigned get(long long step) {
    unsigned a = s, b = 1;
    for (int i = 0; i < 35; ++i) {
        if (step & 1ll) {
            unsigned aa = D[i][0][0] * a + D[i][0][1] * b;
            unsigned bb = D[i][1][0] * a + D[i][1][1] * b;
            a = aa, b = bb;
        }
        step >>= 1;
    }
    return a;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("rps-walk.in", "r", stdin);
    freopen("rps-walk.out", "w", stdout);
    matr a(2, vector <unsigned>(2));
    
    a[0][0] = 1664525;
    a[0][1] = 1013904223;
    a[1][1] = 1;
    
    D[0] = a;
    
    for (int i = 1; i < N; ++i) {
        D[i] = D[i - 1] * D[i - 1];
    }

    int n, m, d;
    scanf("%d%d%d%d", &n, &m, &d, &s);
    
    //cout << n << " " << m << " " << d << " " << s << endl;
    s = (s * 1664525 + 1013904223);
    int x = 0, y = 0;
    unsigned cur = s % 3;
    
    vector <pii> ans;
    
    set <pii> used;
    
    ans.push_back(mp(x, y));
    used.insert(mp(x, y));
    
    long long Q = d * d;
    while (x != n - 1 || y != m - 1) {
        //cout << x << " " << y << endl;
        double dist = sqrt((double)(n - 1 - x) * (n - 1 - x) + (double)(m - 1 - y) * (m - 1 - y));
        dist = max(dist, (double)d);
        int xx = x + d / dist * (n - 1 - x);
        int yy = y + d / dist * (m - 1 - y);
        
        long long best = LLONG_MAX;
        
        int A = -1, B = -1;
        
        unsigned need = (cur + 1) % 3;
        for (int a = xx - 5; a <= xx + 5; ++a) {
            for (int b = yy - 5; b <= yy + 5; ++b) {
                long long di = (long long)(a - x) * (a - x) + (long long)(b - y) * (b - y);
                if (di <= Q && a >= 0 && a < n && b >= 0 && b < m && !used.count(mp(a, b))) {
                    
                    unsigned res = get((long long)a * m + b) % 3;
                    if (res == need) {
                        long long dist = (long long)(n - 1 - a) * (n - 1 - a) + (long long)(m - 1 - b) * (m - 1 - b);
                        if (dist < best) {
                            best = dist;
                            A = a, B = b;
                        }
                    }
                }
            }
        }
        
        if (A == -1) {
            for (int a = xx - 10; a <= xx + 10; ++a) {
                for (int b = yy - 10; b <= yy + 10; ++b) {
                    long long di = (long long)(a - x) * (a - x) + (long long)(b - y) * (b - y);
                    if (di <= Q && a >= 0 && a < n && b >= 0 && b < m && !used.count(mp(a, b))) {
                        
                        unsigned res = get((long long)a * m + b) % 3;
                        if (res == need) {
                            long long dist = (long long)(n - 1 - a) * (n - 1 - a) + (long long)(m - 1 - b) * (m - 1 - b);
                            if (dist < best) {
                                best = dist;
                                A = a, B = b;
                            }
                        }
                    }
                }
            }
            assert(A != -1);
        }
        ans.push_back(mp(A, B));
        used.insert(mp(A, B));
        x = A, y = B, cur = need;
    }
    
    cout << ans.size() - 1 << endl;
    
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
