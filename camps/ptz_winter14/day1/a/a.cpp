#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <cmath>
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
const int maxn = 100500;

int n, sumc, sumw; 

int getval(const string &c)
{
    if (c == "A") return 40;
    if (c == "A-") return 37;
    if (c == "B+") return 33;
    if (c == "B") return 30;
    if (c == "B-") return 27;
    if (c == "C+") return 23;
    if (c == "C") return 20;
    if (c == "C-") return 17;
    if (c == "D") return 13;
    if (c == "D-") return 10;
    if (c == "F") return 00;
    assert(false);
}

bool solve()
{
    if (!(cin >> n)) return false;
    sumc = sumw = 0;
    for (int i = 0; i < n; ++i)
    {
        int cr;
        string mrk;
        cin >> cr >> mrk;
        if (mrk == "P" || mrk == "N") continue;
        sumc += cr * 10;
        sumw += getval(mrk) * cr;
    }
    if (sumc == 0) printf("0.00\n");
    else printf("%.2lf\n", round((double) sumw / sumc * 100) / 100.0);
    return true;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    while (solve());
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
