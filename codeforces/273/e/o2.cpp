#include <unordered_map>
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

struct hmap {
    static int hash(int x) {
        return abs(x*1000000009);
    }
    int sz;
    int *ht, *val;
    hmap() :
        sz(8),
        ht(new int[8]),
        val(new int[8])
    {
        memset(ht, -1, sz * sizeof(int));
        memset(val, 0, sz * sizeof(int));
    }

    int getpos(int x) {
        cout << "hash = " << hash(x) << endl;
        cout << "samp = " << -1294967269 << endl;
        cout << "abs = " << abs(hash(x)) << endl;
        if (hash(x) == -1294967269) {
            cout << "wer" << endl;
            assert(abs(hash(x)) == 1294967269);
        }
        cout << abs(hash(x)) % sz << endl;
        int i = abs(hash(x)) % sz;
        cout << x << " " << i << endl;
        while (ht[i] != x && ht[i] != -1) {
            if (++i == sz) {
                i = 0;
            }
        }
        if (ht[i] == -1) {
            ht[i] = x;
        }
        cout << "pos " << x << " = " << i << endl;
        return i;
    }
};

int main() {
    hmap a;
    for (int i = 0; i < 4; ++i) {
        int res = a.getpos(i);
        printf("a[%d] = %d\n", i, res);
    }
    cout << endl;

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
