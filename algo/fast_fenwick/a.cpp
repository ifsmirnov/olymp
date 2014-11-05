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

const int sz = 1<<5;
int a[sz];
int sp[20];

void fadd(int a[], int n, int i, int x) {
    cout << "add " << n << "   pos = " <<i << endl;
    for (; i < n; i |= (i+1)) {
        a[i] += x;
    }
}

int fget(int a[], int i) {
    int res = 0;
    for (; i >= 0; i = (i&(i+1))-1) {
        res += a[i];
    }
    return res;
}


void add(int i, int x) {
    int k = __builtin_ctz(~i);
    fadd(a+sp[k], sz>>(k+1), i>>(k+1), x);
}
int get(int i) {
    int res = 0;
    int _i = i+1;
    for (int k = 0; _i>>k; ++k) {
        cout << "fget " << k << " " << ((i-(1<<k)+1)>>(k+1)) << endl;
        res += fget(a + sp[k], (i-(1<<(k-1)))>>(k+1));
    }
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    sp[0] = 0;
    for (int i = 1; sz>>i; ++i) {
        sp[i] = sp[i-1] + (sz>>i);
        cout << "st[" << i << "] = " << sp[i] << endl;
    }

    add(0, 1);
    add(1, 10);
    add(2, 100);
    add(3, 1000);
    add(4, 10000);
    add(5, 100000);
    cout << get(4) << endl;
//     forn(i, 10) {
//         add(i, i);
//     }
//     forn(i, 5) {
//         cout << get(i) << endl;
//     }
    cout << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
