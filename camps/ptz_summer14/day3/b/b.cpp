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

int npal(const string& s) {
    set<string> a;
    for (int len = 1; len <= (int)(s.length()); ++len) {
        for (int i = 0; i < (int)s.length() - len + 1; ++i) {
            string t = s.substr(i, len);
            int l = 0, r = len - 1;
            bool ok = true;
            while (l < r) {
                if (t[l] != t[r]) { ok = false; break; }
                ++l; --r;
            }
            if (!ok) continue;
            a.insert(t);
        }
    }
    return a.size();
}

string getms(int n, int x) {
    string s(n, 'a');
    forn(i, n) if (x&(1<<i)) s[i] = 'b';
    return s;
}

string gen1(int n, int k) {
    string s(n, 'a');
    forn(i, n) {
        int t = i%(k+4);
        if (t == k || t == k+2 || t == k+3) s[i] = 'b';
    }
    return s;
}
string gen2(int n, int k) {
    return string(k, 'a') + "bbab" + string(n-k-4, 'a');
}
void solve(int n) {
    vector<string> res(n+1);
    vector<string> c;
    for (int k = 2; k < n/2; ++k) c.pb(gen1(n, k));
    for (int k = 2; k < n-4; ++k) c.pb(gen2(n, k));
    for (const auto& t: c) {
        int np = npal(t);
        if (res[np].empty()) res[np] = t;
    }
    for (int i = 1; i <= n; ++i) {
        cout << i << " : ";
        if (res[i].empty()) cout << "NO" << endl;
        else cout << res[i] << endl;
        assert(i < 8 || !res[i].empty());
    }
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    if (n > 10) {
        solve(n);
    } else {
        vector<string> res(n+1);
        forn(mask, 1<<n) {
            string t = getms(n, mask);
            int np = npal(t);
            if (res[np].empty()) res[np] = t;
        }
        for (int i = 1; i <= n; ++i) {
            cout << i << " : ";
            if (res[i].empty()) cout << "NO" << endl;
            else cout << res[i] << endl;
        }
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
