#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
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
const int inf = 1e9+100500;
const int maxn = 950;

int d[maxn][maxn];
int *dik[maxn], *dkj;

int main() {
#ifdef HOME
#endif
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    int a, b;
    cin >> a >> b;

    if (a == 17 && b == -18) {
        forn(i, maxn) {
            forn(j, maxn) {
                d[i][j] = i * j;
            }
        }

        forn(i, maxn) {
            dik[i] = d[i];
        }
        //dk = d[0];

        forn(k, maxn) {
            forn(i, maxn) {
                dkj = d[k];
                int *dij = d[i];
                int diki = *dik[i];
                forn(j, maxn) {
                    //d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                    *dij = min(*dij, diki + *dkj);
                    ++dkj;
                    ++dij;
                }
            }

            forn(i, maxn) {
                ++dik[i];
            }
        }
    }
    cout << a+b << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
