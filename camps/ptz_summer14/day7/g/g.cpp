#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
const int maxn = 1000500;

int n;
char s[maxn];
char t[maxn];
int mn[maxn];

void buildmn(char c) {
    int last = -inf;
    forn(i, n) {
        if (s[i] == c) mn[i] = min(mn[i], i - last - 1);
        else if (s[i] != '*') last = i;
    }
    last = inf;
    ford(i, n) {
        if (s[i] == c) mn[i] = min(mn[i], last - i - 1);
        else if (s[i] != '*') last = i;
    }
}

void solve() {
    forn(i, n) mn[i] = inf;
    forn(i, 26) buildmn('A'+i);
//     forn(i, n) cout << mn[i] << " "; cout << endl;
    int k = inf;
    forn(i, n) if (s[i] != '*') k = min(k, mn[i]);
    if (k > n) {
        printf("1\n");
        return;
    } else {
        printf("%d\n", n-k);
    }
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    scanf("%s", s);
    n = strlen(s);
    solve();

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
