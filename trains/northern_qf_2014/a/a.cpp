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

const int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("alarm.in", "r", stdin);
    freopen("alarm.out", "w", stdout);

    int n;
    cin >> n;
    fore(i, 0, 23) fore(j, 0, 59) {
        if (c[i/10] + c[i%10] + c[j/10] + c[j%10] == n) {
            printf("%02d:%02d\n", i, j);
            return 0;
        }
    }
    printf("Impossible\n");


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
