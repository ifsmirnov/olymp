#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <functional>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <cstdlib>
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
const int maxn = 1005000;

int cnt[maxn];

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif
    
    int N, T;
    cin >> N >> T;
    priority_queue<int> s;
    i64 res = 0;
    forn(i, N) {
        cnt[i + 1] = 1;
        res += i + 1;
    }
    i64 ans = res;
    int bi = 0;
    int mx = N;
    for (int i = 1; i < N; ++i) {
        int t = 1;
        while (t < mx) {
            res += t - mx;
            ++cnt[t];
            --cnt[mx];
            while (!cnt[mx]) {
                --mx;
            }
            t += i + 1;
        }
        i64 lans = res + 1LL * i * T;
        if (lans < ans) {
            ans = lans;
            bi = i;
        }
    }
    cout << ans << '\n' << bi << '\n';
    forn(i, N) {
        cnt[i + 1] = 1;
    }
    mx = N;
    for (int i = 1; i <= bi; ++i) {
        int t = 1;
        while (t < mx) {
            ++cnt[t];
            --cnt[mx];
            while (!cnt[mx]) {
                --mx;
            }
            t += i + 1;
        } 
    }
    /*for (int i = 1; i <= N; ++i) {
        cout << cnt[i] << ' ';
    }
    cout << '\n';*/
    int st = 0;
    forn(i, bi) {
        int t = 1, j = 0;
        while (cnt[t + j * (i + 1)]) {
            --cnt[t + j * (i + 1)];
            ++j;
        }
        st += j;
        cout << st << ' ';
    }
    cout << '\n';

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
