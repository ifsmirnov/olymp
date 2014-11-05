#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstring>
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
const int maxn = 50;

i64 c[maxn][maxn];
void compc() {
    c[0][0] = 1;
    fore(n, 1, 35) {
        c[n][0] = c[n][n] = 1;
        fore(k, 1, n-1)
            c[n][k] = c[n-1][k] + c[n-1][k-1];
    }
}

int n;
char s[maxn];
int t[maxn];

i64 pc(int n) {
    i64 res = 1;
    forn(i, 26) {
        res *= c[n][t[i]];
        n -= t[i];
    }
    return res;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif

    compc();
    cin >> s;
    n = strlen(s);
    i64 res = 0;
    forn(i, n) t[s[i]-'a']++;
    pc(n);
    forn(i, n-1) {
        forn(j, s[i]-'a') if (t[j]) {
            --t[j];
            res += pc(n-i-1);
            ++t[j];
        }
        --t[s[i]-'a'];
    }
    cout << res + 1 << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
