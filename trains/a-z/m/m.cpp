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
#include <cmath>
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

int msq(int n) {
    int res = 1;
    for (int i = 2; i*i <= n; ++i) {
        while (n % (i*i) == 0) {
            res *= i;
            n /= i*i;
        }
        if (n%i == 0) {
            n /= i;
        }
    }
    return res;
}

int len(int a, int b, int c, int d) {
    a = c-a;
    b = b-d;
    return a*a+b*b;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int r1 = len(a, b, c, d);
    cin >> a >> b >> c >> d;
    int r2 = len(a, b, c, d);
    int s1 = msq(r1);
    int s2 = msq(r2);
    int g = __gcd(s1, s2);
//     cout << r1 << " " << r2 << endl;
//     cout << s1 << " " << s2 << endl;
//     cout << "res: " << r1/s1/s1 << " " << r2/s2/s2 << endl;
    if (r1/s1/s1 == r2/s2/s2) {
        printf("YES\n%.6lf\n", sqrt((double)(r1/s1/s1)) * g);
    } else {
        cout << "NO" << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
