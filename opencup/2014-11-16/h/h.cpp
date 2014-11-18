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
const int maxn = 3030;
// #warning masn

#define GET(x, i) (7&((x)>>((i)*3)))
#define SET(x, i, t) ((x) | ( ((1ll<<(t))) << ((i)*3) ) )
#define MM(i) (7ll<<((i)*3))

int n;
char s[maxn];
int idx[maxn];
int pos[maxn];
int ns;
i64 ms[maxn][maxn];
bool can[maxn][maxn];
char code[1000];
const char rcode[] = ".RG.B";

void scan() {
    scanf("%s", s);
    n = strlen(s);
    ns = 0;
    forn(i, n) {
        if (s[i] == '*') {
            pos[ns] = i;
            idx[i] = ns++;
        }
    }

    code['R'] = 0;
    code['G'] = 1;
    code['B'] = 2;
}

string bin(i64 m) {
    string s;
    forn(i, ns) {
        int x = m & 7; m >>= 3;
        s += rcode[x];
    }
    return s;
}

void fillms() {
    forn(i, n) forn(j, n) {
        can[i][j] = 0;
        ms[i][j] = 0;
    }
    forn(i, n) if (i) {
        for (int len = 1; i + len <= n; ++len) {
            if (s[len-1] != s[i+len-1] && s[len-1] != '*' && s[i+len-1] != '*') {
                break;
            }
            can[i][len] = 1;
            i64 m = 0;
            for (int k = 0; k < ns && pos[k] < len; ++k) {
                int a = pos[k];
                int b = pos[k] + i;
                assert(s[a] == '*');
                if (s[b] != '*') {
                    m = SET(m, k, code[s[b]]);
                }
            }
            ms[i][len] = m;
        }
    }
}

bool solve(int len, i64 fix) {
//     cout << "solve " << len << " " << bin(fix) << endl;
    int l = len;
    for (int i = 0;; ++i) {
        if (l >= n) {
            return true;
        }
        if (i > l) {
            return false;
        }
        if (can[i][len] && ((fix & ms[i][len]) == ms[i][len])) {
            l = i+len;
        }
    }
}

bool solve(int len) {
//     forn(i, n) {
//         cout << s[i] << " -> " << bin(ms[i][len]) << endl;
//     }
    vector<int> rq; // remained questions
    i64 need_fix = 0; // fixed questions
    forn(i, len) {
        if (s[i] == '*') {
            if (s[n - len + i] == '*') {
                if (len * 2 >= n) {
                    need_fix = SET(need_fix, idx[i], code['R']);
                } else {
                    rq.pb(idx[i]);
                }
            } else {
                need_fix = SET(need_fix, idx[i], code[s[n - len + i]]);
            }
        }
    }
//     cout << len << ": ";
//     cout << bin(need_fix) << " ";
//     for (auto x: rq) cout << x << " ";
//     cout << endl;

//     if (rq.empty()) {
//         if (solve(len, need_fix)) {
//             forn(i, len) {
//                 if (s[i] == '*') {
//                     cout << rcode[max(1ll, GET(need_fix, idx[i]))];
//                 } else {
//                     cout << s[i];
//                 }
//             }
//             cout << endl;
//             return true;
//         } else {
//             return false;
//         }
//     }

    forn(m, 1<<rq.size()) {
        for (int sm = m; ; sm = (sm - 1) & m) {
//             cout << m << " " << sm << endl;
            i64 fix = need_fix;
            forn(i, rq.size()) {
                int x = (1&(m>>i)) + (1&(sm>>i));
                fix = SET(fix, rq[i], x);
            }
            if (solve(len, fix)) {
                forn(i, len) {
                    if (s[i] == '*') {
                        cout << rcode[max(1ll, GET(fix, idx[i]))];
                    } else {
                        cout << s[i];
                    }
                }
                cout << endl;
                return true;
            }

            if (sm == 0) {
                break;
            }
        }
    }

    return false;
}

void solve() {
//     cout << s << endl;
    fillms();
    fore(i, 1, n-1) {
        if (solve(i)) {
            return;
        }
    }
    forn(i, n) {
        if (s[i] == '*') {
            cout << 'B';
        } else {
            cout << s[i];
        }
    }
    cout << endl;
}


int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    int t; cin >> t;
    forn(i, t) {
        scan();
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
