#include <functional>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <sstream>
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

vector<string> readString() {
    string s;
    while (s.size() <= 1u) {
        getline(cin, s);
    }
    vector<string> a;
    stringstream ss(s);
    while (ss >> s) {
        a.pb(s);
    }
    return a;
}

void solve() {
    vector<string> a = readString();
    set<string> fb;
    vector<string> b;
    while (1) {
        b = readString();
        if (b.size() == 3u) {
            fb.insert(b.back());
        } else {
            break;
        }
    }
    forn(i, a.size()) {
        if (!fb.count(a[i])) {
            cout << a[i] << " ";
        }
    }
    cout << "\n";
}

int main() {
#ifdef HOME
    freopen("input.txt", "r", stdin);
#endif

    ios::sync_with_stdio();
    int t;
    cin >> t;
    forn(i, t) {
        solve();
    }


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
