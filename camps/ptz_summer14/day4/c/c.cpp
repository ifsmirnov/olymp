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
const int maxn = 100500;

int n, m;
double x[maxn][8];
int f[10] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };

void scan() {
    scanf("%d%d", &n, &m);
    forn(i, m) forn(j, n) scanf("%lf", &x[i][j]);
//     forn(i, m) forn(j, n) x[i][j] = (double)rand()/RAND_MAX;
}

string s;
int a[10];
string str() {
    string s;
    forn(i, n) {
        s += '0' + a[i];
        s += ' ';
    }
    return s;
}
void print_all(int pos) {
    s += str();
    if (pos == n) {
        printf("%s\n", s.c_str());
    } else {
        forn(i, n) if (a[i] == 0) {
            ++a[i];
            print_all(pos+1);
            --a[i];
        }
    }
    s.resize(pos*n*2);
}

void solve() {
    printf("%d\n", f[n]);
    print_all(0);
    forn(i, m) {
//         forn(j, n) cout << x[i][j] << " "; cout << endl;
        int c = 0;
        forn(j, n) {
            int k = max_element(x[i], x[i]+n) - x[i];
//             cout << k << " ";
            x[i][k] = -1;
            forn(t, n) {
                if (t == k) {
                    break;
                }
                if (x[i][t] > -0.5) {
                    c += f[n-j-1];
                }
            }
        }
//         cout << endl;
        assert(c < f[n]);
        printf("%d\n", c+1);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scan();
    solve();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
