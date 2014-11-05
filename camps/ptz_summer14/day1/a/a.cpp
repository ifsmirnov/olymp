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

void go(int a, int b, int n = -1) {
    if (n == -1) n = a*b + 10;
    string t(++n, '.');
    forn(i, n) forn(j, n) if (a*i + b*j < n) t[a*i + b*j] = '+';
    cout << t << endl;
    forn(i, n) {
        t[i] = ' ';
        if (i%5 == 0) t[i] = '.';
        if (i%10 == 0) t[i] = '+';
        if (i%50 == 0) t[i] = '|';
    }
    cout << t << endl;
    cout << endl;
}

void draw(int a, int b, int k) {
    if (a < b) swap(a, b);
    forn(db, a) {
        forn(i, 10) {
            int x = b * db + a * i;
            if (x > k && x - a <= k) {
                printf(" |");
            } else {
                printf("  ");
            }

//             if (i >= 2 * db) {
                printf("%3d", x);
//             } else {
//                 printf("  .");
//             }
        }
        printf("\n");
    }
}

void cont_frac(int a, int b) {
    cout << "[";
    cout << a/b << "; ";
    a %= b;
    swap(a, b);
    while (b) {
        cout << a/b;
        a %= b;
        swap(a, b);
        if (b) cout << ", ";
        else cout << "]" << endl;
    }
}

void get_diff(int a, int b) {
    forn(i, b) {
        int cnt = 0;
        fore(j, i*a, i*a+a-1) cnt += (j%b == 0);
        cout << cnt << " ";
    }
    cout << endl;
}

void f(int a, int b) {
    get_diff(a, b);
    cont_frac(a, b);
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    while (1) {
        int x, y;
        cin >> x >> y;
        f(x, y);
        cout << endl;
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
