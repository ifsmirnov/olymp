#include <iostream>
#include <cstdio>
#include <vector>
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

char sc[1000010];
/*pair<string, int> s[maxn];
int pref[maxn], suf[maxn];*/

/*int lcp(const string &s, const string &t) {
    int i = 0;
    while (i < min(s.size(), t.size()) && s[i] == t[i]) {
        ++i;
    }
    return i;
}*/

struct TNode {
    int next[4];
    int d;
    vector<int> fin;
    
    TNode()
        : d(0)
    {
        forn(i, 4) {
            next[i] = -1;
        }
    }
};

TNode t[maxn];
int tc = 1;
int decode[256];
int res = 0;
vector<pii> ans;

void add(const string &s, int x) {
    int node = 0;
    forn(i, s.size()) {
        int c = decode[s[i]];
        if (t[node].next[c] == -1) {
            t[node].next[c] = tc++;
            t[tc - 1].d = t[node].d + 1;
            
        }
        node = t[node].next[c];
    }
    t[node].fin.pb(x);
}

int dfs(int node) {
    if (node == -1) {
        return -1;
    }
    vi &q = t[node].fin;
    forn(i, 4) {
        int x = dfs(t[node].next[i]);
        if (x != -1) {
            q.pb(x);
        }
    }
    forn(i, t[node].fin.size() / 2) {
        res += t[node].d;
        ans.pb(mp(q[2 * i], q[2 * i + 1]));
        //cerr << res << ' ' << t[node].d << '\n';
    }
    return q.size() % 2 ? q.back() : -1;
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    forn(i, 4) {
        decode["ACGT"[i]] = i;
    }

    int N;
    scanf("%d", &N);
    forn(i, N) {
        scanf("%s", sc);
        add(string(sc), i);
    }
    dfs(0);
    printf("%d\n", res);
    forn(i, ans.size()) {
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    }
    
#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
