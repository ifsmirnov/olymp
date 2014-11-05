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
const int maxn = 25;

int n;
char cur[maxn];
void go(int pos, int bal) {
    int lft = n*2 - pos;
    if (lft == 0) {
        printf("%s\n", cur);
        return;
    }
    if (bal+1 <= lft-1) {
        cur[pos] = '(';
        go(pos+1, bal+1);
    }
    if (bal > 0) {
        cur[pos] = ')';
        go(pos+1, bal-1);
    }

}

int main() {
#ifdef HOME
#endif
    freopen("paren.in" ,"r", stdin);
    freopen("paren.out", "w", stdout);

    cin >> n;
    go(0, 0);

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
