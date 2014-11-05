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
const int maxn = 5050;

bool same(int a, int b) {
    return tolower(a) == tolower(b) && a != b;
}

int n;
string s;
vector<pii> st;

int res[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> s;
    int l = 0, r = 0;
    int k = 0;
    forn(i, n*2) {
        if (islower(s[i])) {
            st.pb(mp(s[i], l++));
        } else {
            st.pb(mp(s[i], r++));
        }
        ++k;

        if (k >= 2 && same(st[k-1].fi, st[k-2].fi)) {
            pii a = st.back(); st.pop_back(); --k;
            pii b = st.back(); st.pop_back(); --k;
            if (islower(a.fi)) {
                res[b.se] = a.se+1;
            } else {
                res[a.se] = b.se+1;
            }
        }
    }
    if (k == 0) {
        forn(i, n) printf("%d%c", res[i], " \n"[i == n-1]);
    } else {
        printf("Impossible\n");
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
