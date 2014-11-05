#include <functional>
#include <cstring>
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
const int maxn = 1000060;

int n;
char c[maxn];
int b[maxn];

bool ok() {
    int bal = 0;
    forn(i, n) {
        if (c[i] == '(') ++bal;
        else --bal;
        if (bal < 0) return false;
    }
    return bal == 0;
}

void None() { printf("None\n"); exit(0); }

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    scanf("%s", c);
    n = strlen(c);
    if (n%2) { None(); }
    int bal = 0;
    int k = 0;
    forn(i, n) {
        b[i] = (c[i] == '?');
        if (c[i] == '(') ++bal;
        else if (c[i] == ')') --bal;
        else ++k;
    }
    assert((k-bal)%2 == 0);

    int op = (k-bal)/2;
    int cl = (k+bal)/2;
    if (op < 0 || cl < 0) { None(); }

    int r;
    int p1 = -1, p2 = -1;
    forn(i, n) if (b[i]) {
        if (r < op) c[i] = '(';
        else c[i] = ')';
        if (r == op - 1) p1 = i;
        else if (r == op) p2 = i;
        ++r;
    }

    if (ok()) {
        if (p1 != -1 && p2 != -1) {
            c[p1] = ')';
            c[p2] = '(';
            if (ok()) { printf("Many\n"); return 0; }
        }
        printf("Unique\n");
    } else None();


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
