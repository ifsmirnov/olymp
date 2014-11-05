#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define fore(i, b, e) for (int i = (int)(b); i <= (int)(e); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define mp make_pair

int f(const string& s, int k) {
    int res = 0;
    int n = s.length();
    for (int len = 1; len <= k; ++len) {
        forn(i, n-len+1) {
            string t = s.substr(i, len);
            if (t == string(t.rbegin(), t.rend())) {
//                 cout << t << endl;
                ++res;
            }
        }
    }
    return res;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    int n, k, q;
    cin >> s >> k >> q;
    forn(i, q) {
        char t[5];
        int x, l, r;
        cin >> x >> l >> r;
        --l; --r;
        if (x == 2) {
            cout << f(s.substr(l, r-l+1), k) << endl;
        } else {
            cin >> t;
            for (int j = l; j <= r; ++j) s[j] = t[0];
        }
    }
}
