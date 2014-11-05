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

const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
#define ok(x,y) ((x)>=0&&(y)>=0&&(x)<n&&(y)<m)

int n, m;
int a[10][10];
bool ff() {
    forn(i, n) forn(j, m) {
        int cnt = 0;
        forn(k, 4) if (ok(i+dx[k], j+dy[k])) cnt ^= a[i+dx[k]][j+dy[k]];
        if (cnt%2) {
//             forn(I, n) {
//                 forn(J, m) cout << a[I][J];
//                 cout << endl;
//             }
//             cout << "false" << endl;
            return false;
        }
    }
    return true;
}

int count(int n, int m) {
    ::n = n;
    ::m = m;
    int cnt = 0;
    forn(mask, 1<<(n*m)) {
        forn(i, n) forn(j, m) a[i][j] = 0 != (mask&(1<<(i*m+j)));
        cnt += ff();
    }
    return cnt;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    while (1) {
        int x, y;
        cin >> x >> y;
        cout << count(x, y) << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
