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

int n, s, k;
int c[100][100];
int d[100][100];
bool t[100];

int des[] = {1, 1, 2, 5, 14, 42, 0};
int bad_mask[1<<3];
int check() { // 1: ok; 0: nothing; -1: too many
//     forn(i, n) {
//         forn(j, s) cout << c[i][j] << " ";
//         cout << endl;
//     }
//     cout << endl;

    forn(i, n) forn(j, 7) d[j][i] = 0;

    d[0][0] = 1;
    forn(i, 6) {
        forn(j, n) {
            forn(k, s) if (c[j][k])
                d[i+1][c[j][k]-1] += d[i][j];
        }
    }

    forn(i, 1<<(n-1)) bad_mask[i] = 1;
    forn(i, 7) {
        forn(tm, 1<<(n-1)) {
            int mask = (tm<<1)|1;
            int cnt = 0;
            forn(j, n) if (mask&(1<<j)) cnt += d[i][j];
            if (cnt > des[i])
                bad_mask[tm] = -1;
            else if (cnt != des[i] && bad_mask[tm] != -1)
                bad_mask[tm] = 0;
        }
    }

    bool f0 = false;
    forn(tm, 1<<(n-1)) {
        if (bad_mask[tm] == 1) {
            tm = (tm<<1)|1;
            forn(i, n) t[i] = 0 != (tm&(1<<i));
            return 1;
        } else if (bad_mask[tm] == 0) {
            f0 = true;
        }
    }
    if (f0) return 0;
    else return -1;
}

bool check_degs(int k) {
    static int c[10];
    forn(i, n) c[i+1] = 0;
    forn(i, s) c[::c[k][i]]++;
    fore(i, 1, n-1) if (c[i] < c[i+1]) return false;
    return true;
}

bool check_degs() {
    if (!check_degs(0)) return false;
//     forn(i, n) if (!check_degs(i)) return false;
    return true;
}

bool go(int cn, int cs) {
//     cout << cn << " " << cs << endl;
//     if (cn == 0 && !check_degs()) return false;
    if (cn == 0 && !check_degs()) return false;
    int cv = check();
    if (cv == -1) return 0;
    if (cv == 1) return 1;
    if (cs == s) ++cn, cs = 0;
    if (cn == n) return 0;

    int b = 1;
    if (cs) b = c[cn][cs - 1];
//     for (int i = n; i >= b; --i) {
    fore(i, b, n) {
        c[cn][cs] = i;
        if (go(cn, cs+1)) return true;
        if (cn == 0 && cs == 0) break;
//         if (i == b+1) break;
    }
    c[cn][cs] = 0;
    if (cn || cs) {
        if (go(cn, s)) return true;
    }
    return false;
}

int cpos[10];

// bool go(int cn, int cs) {
//     if (cn == 0 && !check_degs()) return false;
//     int cv = check();
//     if (cv == -1) return 0;
//     if (cv == 1) return 1;
//     if (cs == n) ++cn, cs = 0;
//     if (cn == n) return 0;
// 
// //     forn(i, n) {
// //         forn(j, s) cout << c[i][j] << " ";
// //         cout << endl;
// //     }
// //     cout << endl;
// 
//     int rp = cpos[cn];
//     fore(i, rp, s-1) c[cn][i] = cs+1;
//     for (int i = s-1; i >= rp; --i) {
//         cpos[cn] = i+1;
//         if (go(cn, cs+1)) return true;
//         c[cn][i] = 0;
//     }
//     cpos[cn] = rp;
//     return go(cn, cs+1);
// }

void out() {
    cout << "found " << n << " " << s << endl;
    forn(i, n) cout << t[i] << " "; cout << endl;
    forn(i, n) {
        forn(j, s) cout << c[i][j] << " "; cout << endl;
    }
}

void solve(int k) {
    des[6] = k;
    n = 4;
//     n = 4;
//     s = 10;
//     if (go(0,0)) {
//         out();
//     }
//     return;
    while (1) {
        for (s = 2; s <= 5; ++s) {
            cout << "go " << n << " " << s << endl;
            if (go(0, 0)) {
                out();
                return;
            }
            cout << clock()/1000 << endl;
        }
        ++n;
    }
}

void output(int n) {
if (n == 120) {
printf("4 12\n\
1 0 0 0 \n\
1 2 3 3 4 4 4 4 0 0 0 0 \n\
1 3 4 4 4 4 4 4 4 4 4 4 \n\
2 4 0 0 0 0 0 0 0 0 0 0 \n\
3 0 0 0 0 0 0 0 0 0 0 0 \n\
\n");}
if (n == 121) {
printf("4 5\n\
1 0 1 0 \n\
1 2 0 0 0 \n\
3 4 0 0 0 \n\
1 1 4 4 0 \n\
1 2 2 2 2 \n\
\n");}
if (n == 122) {
printf("4 4\n\
1 0 0 0 \n\
1 2 0 0 \n\
1 2 3 0 \n\
1 4 4 4 \n\
1 2 2 2 \n\
\n");}
if (n == 123) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 0 \n\
1 3 3 4 \n\
2 2 0 0 \n\
2 3 3 0 \n\
\n");}
if (n == 124) {
printf("4 3\n\
1 0 0 0 \n\
1 2 3 \n\
1 3 3 \n\
2 2 4 \n\
2 3 3 \n\
\n");}
if (n == 125) {
printf("4 3\n\
1 0 0 0 \n\
1 2 3 \n\
1 3 4 \n\
2 2 3 \n\
2 3 3 \n\
\n");}
if (n == 126) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 0 \n\
1 2 3 4 \n\
2 4 0 0 \n\
2 3 3 0 \n\
\n");}
if (n == 127) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 4 \n\
1 2 3 3 \n\
3 4 4 0 \n\
2 4 0 0 \n\
\n");}
if (n == 128) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 4 \n\
1 2 3 0 \n\
3 4 4 4 \n\
2 3 0 0 \n\
\n");}
if (n == 129) {
printf("4 4\n\
1 0 0 1 \n\
1 2 2 3 \n\
2 2 2 3 \n\
4 0 0 0 \n\
1 0 0 0 \n\
\n");}
if (n == 130) {
printf("4 3\n\
1 0 0 0 \n\
1 2 3 \n\
1 2 2 \n\
3 3 4 \n\
2 4 4 \n\
\n");}
if (n == 131) {
printf("3 4\n\
1 0 0 \n\
1 2 3 0 \n\
1 2 0 0 \n\
2 3 3 3 \n\
\n");}
if (n == 132) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 4 \n\
1 2 3 4 \n\
2 3 0 0 \n\
3 4 4 4 \n\
\n");}
if (n == 133) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 4 \n\
1 2 3 3 \n\
2 4 4 4 \n\
3 4 4 0 \n\
\n");}
if (n == 134) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 0 \n\
1 2 2 3 \n\
3 3 3 4 \n\
2 3 3 0 \n\
\n");}
if (n == 135) {
printf("4 4\n\
1 0 0 0 \n\
1 2 3 4 \n\
1 2 3 3 \n\
2 4 4 0 \n\
3 4 4 4 \n\
\n");}
if (n == 136) {
printf("4 5\n\
1 0 0 0 \n\
1 2 3 4 0 \n\
1 2 3 3 4 \n\
2 0 0 0 0 \n\
3 4 4 4 4 \n\
\n");}
if (n == 137) {
printf("4 5\n\
1 0 0 0 \n\
1 2 3 4 0 \n\
1 2 3 3 0 \n\
2 4 0 0 0 \n\
3 4 4 4 4 \n\
\n");}
if (n == 138) {
printf("4 5\n\
1 0 0 0 \n\
1 2 3 0 0 \n\
1 2 2 0 0 \n\
3 3 3 3 4 \n\
2 3 3 3 3 \n\
\n");}
if (n == 139) {
printf("4 5\n\
1 0 0 0 \n\
1 2 3 0 0 \n\
1 3 3 4 0 \n\
2 2 0 0 0 \n\
2 4 4 4 4 \n\
\n");}
if (n == 140) {
printf("4 5\n\
1 0 0 0 \n\
1 2 3 0 0 \n\
1 2 3 3 3 \n\
2 4 4 4 0 \n\
3 4 4 4 4 \n\
\n");}
}

int main() {
#ifdef HOME
//     freopen("res", "r", stdin);
#endif

    /**
        The backtracking you could find in this code was not
        able to find the answer for k=120 :( My teammate wrote
        some other stuff to do it.
    */
    freopen("catalan.in", "r", stdin);
    freopen("catalan.out", "w", stdout);
//     freopen("output.txt", "w", stdout);
//     cin >> k;
//     solve(k);
//     return 0;
    int n;
    while (cin >> n) output(n);
//     while (cin >> des[6]) {
//         printf("if (n == %d) {\n", des[6]);
//         printf("printf(\"");
//         cin >> n >> s;
//         cout << n << " " << s << "\\n\\" << endl;
//         forn(i, n) { cin >> t[i]; cout << t[i] << " "; } cout << "\\n\\" << endl;
//         forn(i, n) {
//             forn(j, s) { cin >> c[i][j]; cout << c[i][j] << " "; }
//             cout << "\\n\\" << endl;
//         }
//         printf("\\n\");}\n");
//         if (check() != 1) {
//             cout << "error@" << des[6] << endl;
//         }
//     }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
