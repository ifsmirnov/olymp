#include <unordered_map>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cmath>
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
typedef double ld;

const int maxn = 410;

int dist(const pii& a, const pii& b) {
    return abs(a.fi - b.fi) + abs(a.se - b.se);
}

int tn;
int n, m, k;
int a[maxn][maxn];
pii order[maxn*maxn];
int sc[maxn*10];

void out(ostream& out = std::cout) {
    forn(i, n) forn(j, m) out << a[i][j] + 1 << " \n"[j == m-1];
}

void init() {
    k = 0;
    forn(i, n) forn(j, m) order[k++] = mp(i, j);
}

int solve6() {
    k = 0;
    forn(i, n) forn(j, m) order[k++] = mp(i, j);
    vector<pii> norder(order, order+k);
    int l = 0, r = k-1;
    k = 0;
    while (1) {
        if (l <= r) order[k++] = norder[l++];
        else break;
        if (l <= r) order[k++] = norder[r--];
        else break;
    }
    int res = 0;
    forn(i, k) {
       a[order[i].fi][order[i].se] = i;
       if (i+1 != k) {
           res = max(res, ++sc[dist(order[i], order[i+1])]);
       }
    }
    return res;
}

int solve_greedy() {
    forn(i, n+m+5) sc[i] = 0;
    pii s = mp(0, 0);
    forn(i, n) forn(j, m) a[i][j] = -1;
    a[0][0] = 0;
    int res = 0;
    forn(i, k-1) {
        pii nxt(-1, -1);
        pii mx(10000000, -1);
        forn(i, n) forn(j, m) if (a[i][j] == -1) {
            int d = dist(mp(i, j), s);
            if (mp(sc[d], -d) < mx) {
                mx = mp(sc[d], -d);
                nxt = mp(i, j);
            }
        }
//         cout << "d = " << -mx.se << endl;
        s = nxt;
        a[s.fi][s.se] = i+1;
        res = max(res, ++sc[-mx.se]);
    }
    return res;
}

int eval() {
    forn(i, n+m+5) sc[i] = 0;
    int res = 0;
    forn(i, k) {
       if (i+1 != k) {
           res = max(res, ++sc[dist(order[i], order[i+1])]);
       }
    }
    return res;
}

void make_better() {
    int d = max_element(sc, sc+n+m+5) - sc;
    vector<int> bi;
    vector<pii> bv;
    forn(i, k-1) {
        if (dist(order[i], order[i+1]) == d) {
            bi.pb(i);
            bv.pb(order[i]);
//             bi.pb(i+1);
//             bv.pb(order[i+1]);
        }
    }
    random_shuffle(all(bv));
    bi.resize(min(4, (int)bi.size()));
    bv.resize(min(4, (int)bv.size()));
    forn(i, bv.size()) {
        order[bi[i]] = bv[i];
    }
}

void restore() {
    forn(i, k) a[order[i].fi][order[i].se] = i;
}

int solve_random() {
    forn(i, n+m+5) sc[i] = 0;
    random_shuffle(order, order + k);
    int res = 0;
    forn(i, k) {
       a[order[i].fi][order[i].se] = i;
       if (i+1 != k) {
           res = max(res, ++sc[dist(order[i], order[i+1])]);
       }
    }
    return res;
}

int solve(int iter = 40000) {
//     random_shuffle(order, order+k);
    solve6();
    int cur_score = eval();
    cerr << "cur_score = " << cur_score << endl;
    restore();
    forn(i, iter) {
        make_better();
        int new_score = eval();
        if (new_score < cur_score) {
            cerr << "new_score = " << new_score << endl;
            cur_score = new_score;
            restore();
        }
    }
    return cur_score;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
//     freopen("pap05.in", "r", stdin);
#endif

//     srand(2);
    long long seed;
    asm("rdtsc":"=A"(seed));
    srand(seed);

    cin >> n >> m >> tn;
    string filename = "res/resXX.out";
    sprintf(const_cast<char*>(filename.c_str()) + 7, "%02d", tn);
    filename[9] = '.';
    cout << filename << endl;

    init();

    while (1) {
        fstream fin(filename, ios::in);
        int cur_res;
        if (!(fin >> cur_res)) {
            cur_res = 100000000;
        }
        fin.close();

        int res = solve();
        if (res < cur_res) {
            fstream fout(filename, ios::out);
            fout << res << endl;
            out(fout);
            fout.close();
            cerr << "updated " << res <<
                    " for " << n << " " << m << " (" << tn << ")" << endl;
        }
//         if (6 <= tn && tn <= 8) {
//             break;
//         }
//         break;
    }

#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
