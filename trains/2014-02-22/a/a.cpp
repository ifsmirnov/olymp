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
const int maxn = 100500;

bool ends(string s, string t) {
    if (s.length() < t.length()) return false;
    return s.substr(s.length() - t.length()) == t;
}
bool cons(char c) {
    return string("aeiouy").find(c) == string::npos;
}

int main() {
#ifdef HOME
//     freopen("input.txt", "r", stdin);
#endif
    freopen("afftar.in", "r", stdin);
    freopen("afftar.out", "w", stdout);

    string s;
    cin >> s;
    if (ends(s, "o") || ends(s, "s") || ends(s, "ch") || ends(s, "sh") || ends(s, "x")) {
        s += "es";
    } else if (s[s.length() - 1] == 'y' && s.length() != 1u && cons(s[s.length() - 2])) {
        s = s.substr(0, s.length() - 1) + "ies";
    } else {
        s += "s";
    }
    cout << s << endl;


#ifdef HOME
    cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
