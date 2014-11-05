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

#define pc __builtin_popcount

string bin(int x, int n) {
    string s;
    forn(i, n) s += '0'+x%2, x /= 2;
    return s;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("combo2.in", "r", stdin);
    freopen("combo2.ovt", "w", stdout);

    int n, k;
    cin >> n >> k;
    int cur = 0;
    forn(i, 1<<n) {
        int x = i^(i>>1);
        if (pc(x) != k) continue;

//         cout << bin(x, n) << endl;
        int cnt = 0;
        forn(j, n) if (x&(1<<j)) {
            ++cnt;
            printf("%d", j+1);
            if (cnt == k)
                printf("\n");
            else
                printf(" ");
        }

        if (cur && pc(x^cur) != 2) {
            cout << "rerr" << endl;
        }
        cur = x;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
